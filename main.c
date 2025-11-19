#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix.h"

int main() {
    // Step 1 : Create a graph
    t_adjacency_list* graph = readGraph("../data/exemple_meteo.txt");

    displayAdjacencyList(graph);
    printf("\n");
    float** matrix = createMatrix(graph);
    displayMatrix(matrix, graph->size);
    freeMatrix(matrix, graph->size);
    float** A = matrixMultiplication(matrix,matrix,graph->size);
    A = matrixMultiplication(A,matrix,graph->size);
    displayMatrix(A, graph->size);
    for (int i = 0; i < 4; i++) {
        A = matrixMultiplication(matrix,matrix,graph->size);
    }
    displayMatrix(A, graph->size);
    // Step 2 : Check the graph
    printf("--- Validation of step 2 ---\n");
    isMarkovGraph(graph);
    printf("\n");

    // Step 3 : Drawing the graph
    printf("--- Validation of step 3 ---\n");
    representationGraph(graph);
    printf("Result in ../data/Output.txt\n");

    return 0;
}