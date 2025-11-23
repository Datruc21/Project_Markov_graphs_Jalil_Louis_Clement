//
// Created by Louis on 20/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix.h"

int main() {
    const char* filename = "../data/exemple_valid_step3.txt";
    t_adjacency_list* graph = readGraph(filename);

    if (graph == NULL) {
        return 1;
    }
    printf("--- Graph Loaded (%d vertices) ---\n", graph->size);
    displayAdjacencyList(graph);
    printf("\n");

    printf("--- Running Tarjan's Algorithm ---\n");
    t_partition* scc_partition = tarjanAlgorithm(*graph);

    printf("\n--- Validation of Step 2 (Part 3) ---\n");
    printf("\n");
    float** matrix = createMatrix(graph);
    float** submatrix1 = subMatrix(matrix,scc_partition,16);
    displayMatrix(matrix, graph->size);
    printf("\n--- Creating Submatrices (Part 3) ---\n");
    displayMatrix(submatrix1, 1);
}