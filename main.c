#include <stdio.h>
#include "utils.h"

int main() {
    // Step 1 : Create a graph
    printf("--- Validation of step 1 ---\n");
    t_adjacency_list* graph = readGraph("../data/exemple1.txt");
    displayAdjacencyList(graph);
    printf("\n");

    // Step 2 : Check the graph
    printf("--- Validation of step 2 ---\n");
    isMarkovGraph(graph);
    printf("\n");

    // Step 3 : Drawing the graph
    printf("--- Validation of step 3 ---\n");
    representationGraph(graph);
    printf("Result in ../data/Output.txt\n");

    // Just some experiments
    /*
    printf("test1\n");
    float** matrix = createMatrix(graph);
    displayMatrix(matrix, graph->size);
    freeMatrix(matrix, graph->size);

    printf("\ntest2\n");
    float** A = matrixMultiplication(matrix,matrix,graph->size);
    A = matrixMultiplication(A,matrix,graph->size);
    displayMatrix(A, graph->size);
    for (int i = 0; i < 4; i++) {
        A = matrixMultiplication(matrix,matrix,graph->size);
    }
    displayMatrix(A, graph->size);
    */

    return 0;
}