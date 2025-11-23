//
// Created by jalil on 19/11/2025.
//

#include "matrix.h"

float** createZeroMatrix(int size) {
    /*Initialises a matrix of size : size * size with only 0's using calloc
     */
    float** matrix = (float**)calloc(size,sizeof(float*));
    for (int i = 0; i<size; i++) {
        matrix[i] = (float*)calloc(size,sizeof(float));
    }
    return matrix;
}

void copyMatrix(float** src, float** dest, int n) {
    /* copies the matrix from src to dest, both have to be n*n in size
     * uses a simple double loop
     */
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

float** matrixMultiplication(float** A, float** B, int n) {
    float** matrix = createZeroMatrix(n);
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            float sum = 0;
            for (int k = 0; k<n; k++) {
                sum += A[i][k] * B[k][j];
            }
            matrix[i][j] = sum;
        }
    }
    return matrix;
}

void displayMatrix(float** matrix, int size) {
    /*a double for loop to display the contents of a size*size matrix
     *
     */
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

float** identityMatrix(int size) {
    /* A function to create an identity matrix where the main diagonal of the square matrix are 1's
     *
     */
    float** matrix = createZeroMatrix(size);
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            matrix[i][j] = (i == j) ? 1 : 0;
        }
    }
    return matrix;
}


float differenceMatrices(float** A, float** B, int n) {
    /*function to compute the total difference between matrix A and matrix B of size n*n
     */
    float sum = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            /*if else statement to always have a positive or null difference between A[i][j] and B[i][j]
             */
            if (A[i][j] <= B[i][j])
                sum += B[i][j] - A[i][j];
            else
                sum += A[i][j] - B[i][j];
        }
    }
    return sum;
}

float** createMatrix(t_adjacency_list* T) {
    /*function to create a matrix from an adjacency list T
     */
    float** matrix = createZeroMatrix(T->size);
    for (int i = 0; i<T->size; i++) {
        p_cell cur = T->lists[i]->head;
        //while loop to read all the different probabilities for a certain vertice (node)
        while (cur) {
            // arrivalvertex is the ID of the vertex
            matrix[i][cur->arrivalVertex-1] = cur->probability;
            cur = cur->next;
            //single linked list to simplify node traversal
        }
    }
    return matrix;
}


void freeMatrix(float** A, int n) {
    //free a matrix of size n
    for (int i = 0; i<n; i++) {
        free(A[i]);
    }
    free(A);
}



float** subMatrix(float** matrix, t_partition * part, int compo_index) {
    /*creates a submatrix for a given index of a component (group of nodes
     *who can access eachother and ocme back to themselves
     */
    int counter1 = 0;
    int counter2 = 0;
    //check the existence of the component group ID
    if (doesClassExist(part,compo_index)) {
        float** submatrix = createZeroMatrix(part->classes[compo_index]->count);
        //double for loop of the components since they are the only ones which interest us
        for (int i = 0; i<(part->classes[compo_index]->count); i++) {
                for (int j = 0; j<(part->classes[compo_index]->count); j++) {
                        // maps the different nodes of the component to a submatrix
                        submatrix[counter1][counter2] = matrix[part->classes[compo_index]->vertices[i]->id][part->classes[compo_index]->vertices[j]->id];
                        counter2++;
                }
                counter1++;
                counter2=0;
                //increment the position of the next place to fill in the submatrix
        }
        return submatrix;
    } else {
        return NULL;
    }
}

int gcd(int *vals, int nbvals) {
    /* function to return the greatest common divisor
     */
    if (nbvals == 0) return 0;
    int result = vals[0];
    for (int i = 1; i < nbvals; i++) {
        int a = result;
        int b = vals[i];
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        result = a;
    }
    return result;
}

int getPeriod(float** sub_matrix,int n) {
    /* function to calculate the period of a submatrix
     *
     */
    int *periods = (int *)calloc(n , sizeof(int));
    int period_count = 0;
    int cpt = 1;
    float** power_matrix = createZeroMatrix(n);
    copyMatrix(sub_matrix,power_matrix,n);
    power_matrix = matrixMultiplication(power_matrix,sub_matrix,n);
    //for loop to get the last non zero diagonal M^k(i,i) != 0, with k being the current step
    for (cpt = 1; cpt <= n; cpt++)
    {
        int diag_nonzero = 0;
        for (int i = 0; i < n; i++)
        {
            if (power_matrix[i][i] > 0.0f)
            {
                diag_nonzero = 1;
            }
        }
        if (diag_nonzero) {
            periods[period_count] = cpt;
            period_count++;
        }
        //the matrix multiplication of M^k * M with k being the current step, since M^k(i,i) > 0
        // means that at k steps, you can return to yourself in the submatrix
        float** result_matrix = matrixMultiplication(power_matrix, sub_matrix, n);
        copyMatrix(result_matrix,power_matrix,n);
        freeMatrix(result_matrix,n);
    }
    freeMatrix(power_matrix, n);
    //the period A is the greatest common divisor of all the recorded powers k
    int A = gcd(periods, period_count);
    //clean up memory
    free(periods);
    return A;
}