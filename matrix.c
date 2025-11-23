//
// Created by jalil on 19/11/2025.
//

#include "matrix.h"

float** createZeroMatrix(int size) {
    float** matrix = (float**)malloc(sizeof(float*)*size);
    for (int i = 0; i<size; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*size);
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
