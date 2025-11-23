#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifndef INC_2526_TI301_PJT_MATRIX_H
#define INC_2526_TI301_PJT_MATRIX_H

/**
 * @brief Allocates a square matrix initialized to 0.
 */
float** createZeroMatrix(int size);

/**
 * @brief Converts the graph representation from an adjacency list to a transition matrix.
 * @param T Pointer to the graph's adjacency list.
 * @return A dynamically allocated 2D array (float**) representing transition probabilities.
 */
float** createMatrix(t_adjacency_list* T);

/**
 * @brief Displays the content of a matrix to the console.
 * @param matrix The 2D array to display.
 * @param size The dimension of the matrix (NxN).
 */
void displayMatrix(float** matrix, int size);

/**
 * @brief Frees the memory allocated for a matrix.
 * @param matrix The matrix to free.
 * @param size The number of rows in the matrix.
 */
void freeMatrix(float** matrix, int size);

/**
 * @brief Computes the product of two square matrices (A * B).
 * Used to calculate the evolution of probabilities over time steps.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param n The size of the matrices.
 * @return A new matrix containing the result of the multiplication.
 */
float** matrixMultiplication(float** A, float** B, int n);

/**
 * @brief Extracts a submatrix corresponding to a specific Strongly Connected Component (class).
 * Allows analysis of a single class in isolation from the rest of the graph.
 * @param matrix The global transition matrix of the graph.
 * @param part The partition structure containing the classes.
 * @param compo_index The index of the specific class to extract.
 * @return A smaller 2D matrix corresponding only to the vertices of that class.
 */
float** subMatrix(float** matrix, t_partition * part, int compo_index);

/**
 * @brief Helper function to calculate the Greatest Common Divisor (GCD) of an array of integers.
 * Essential for the periodicity calculation.
 * @param vals Array of integer values.
 * @param nbvals Number of elements in the array.
 * @return The GCD of the values.
 */
int gcd(int *vals, int nbvals);

/**
 * @brief Calculates the period of a specific class (Bonus Challenge).
 * Analyzes the diagonal entries of matrix powers to find the cycle length.
 * @param sub_matrix The submatrix representing the class.
 * @param n The size of the submatrix.
 * @return The period of the class (returns 1 if the class is aperiodic).
 */
int getPeriod(float** sub_matrix, int n);

/**
 * @brief Copies content from src matrix to dest matrix.
 */
void copyMatrix(float** src, float** dest, int n);

/**
 * @brief Calculates the total absolute difference between two matrices.
 */
float differenceMatrices(float** A, float** B, int n);

#endif //INC_2526_TI301_PJT_MATRIX_H