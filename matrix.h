//
// Created by jalil on 19/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H

float** createMatrix(t_adjacency_list* T);
void displayMatrix(float** matrix, int size);
void freeMatrix(float** matrix, int size);
float** matrixMultiplication(float** A, float** B, int n);
float** subMatrix(float** matrix, t_partition * part, int compo_index);
int gcd(int *vals, int nbvals);
int getPeriod(float** sub_matrix,int n);



#endif //INC_2526_TI301_PJT_MATRIX_H