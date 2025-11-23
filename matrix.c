//
// Created by jalil on 19/11/2025.
//

#include "matrix.h"

float** createZeroMatrix(int size) {
    float** matrix = (float**)calloc(size,sizeof(float*));
    for (int i = 0; i<size; i++) {
        matrix[i] = (float*)calloc(size,sizeof(float));
        for (int j = 0; j<size; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void copyMatrix(float** src, float** dest, int n) {
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
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

float** identityMatrix(int size) {
    float** matrix = createZeroMatrix(size);
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            matrix[i][j] = (i == j) ? 1 : 0;
        }
    }
    return matrix;
}


float differenceMatrices(float** A, float** B, int n) {
    float sum = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (A[i][j] <= B[i][j])
                sum += B[i][j] - A[i][j];
            else
                sum += A[i][j] - B[i][j];
        }
    }
    return sum;
}

float** createMatrix(t_adjacency_list* T) {
    float** matrix = createZeroMatrix(T->size);
    for (int i = 0; i<T->size; i++) {
        p_cell cur = T->lists[i]->head;
        while (cur) {
            matrix[i][cur->arrivalVertex-1] = cur->probability;
            cur = cur->next;
        }
    }
    return matrix;
}


void freeMatrix(float** A, int n) {
    for (int i = 0; i<n; i++) {
        free(A[i]);
    }
    free(A);
}



float** subMatrix(float** matrix, t_partition * part, int compo_index) {
    int counter1 = 0;
    int counter2 = 0;
    if (doesClassExist(part,compo_index)) {
        float** submatrix = createZeroMatrix(part->classes[compo_index]->count);
        for (int i = 0; i<(part->classes[compo_index]->count); i++) {
                for (int j = 0; j<(part->classes[compo_index]->count); j++) {
                        submatrix[counter1][counter2] = matrix[part->classes[compo_index]->vertices[i]->id][part->classes[compo_index]->vertices[j]->id];
                        counter2++;
                }
                counter1++;
                counter2=0;
        }
        return submatrix;
    } else {
        return NULL;
    }
}

int gcd(int *vals, int nbvals) {
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
    int *periods = (int *)calloc(n , sizeof(int));
    int period_count = 0;
    int cpt = 1;
    float** power_matrix = identityMatrix(n);
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
        float** result_matrix = matrixMultiplication(power_matrix, sub_matrix, n);
        copyMatrix(result_matrix,power_matrix,n);
        freeMatrix(result_matrix,n);
    }
    free(periods);
    freeMatrix(power_matrix, n);
    return gcd(periods, period_count);
}