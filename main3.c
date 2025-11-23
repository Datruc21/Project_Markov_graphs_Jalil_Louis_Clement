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
    displayMatrix(matrix, graph->size);
    printf("\n--- Creating Submatrices (Part 3) ---\n");
    for (int i = 0; i < scc_partition->count; i++) {
        float** submatrix = subMatrix(matrix,scc_partition,i);
        displayMatrix(submatrix, scc_partition->classes[i]->count);
        printf("\n");
        printf("The period is : %d\n",getPeriod(submatrix,scc_partition->classes[i]->count));
        freeMatrix(submatrix, scc_partition->classes[i]->count);
    }
    freePartition(scc_partition);
    return 0;
}