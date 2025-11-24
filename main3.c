#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix.h"

// Helper function to compute power of a matrix (M^p)
// Used for M^3 and M^7
float** matrixPower(float** M, int size, int p) {
    float** res = createZeroMatrix(size);
    float** temp = createZeroMatrix(size);

    copyMatrix(M, res, size);

    for (int k = 1; k < p; k++) {
        float** mult = matrixMultiplication(res, M, size);
        // Free old result and update
        copyMatrix(mult, res, size);
        freeMatrix(mult, size);
    }
    freeMatrix(temp, size);
    return res;
}

int main() {
    // Step 1: Validation of Matrix Calculations
    // This part of the main for step 1 validation was assisted by AI
    /* prompt : Here is the subject of part3 and our matrix.h file. Based on this, can you generate us a main function
     * that meets all the requirements of part3 step1 validation
    */
    // Of course there were so many things to adjust ourselves after
    printf("------- Validation of Step 1 -------\n");

    // 1. Load the graph
    t_adjacency_list* graph_step1 = readGraph("../data/exemple_meteo.txt");
    if (graph_step1 == NULL) {
        return 1;
    }

    // 2. Create and Display Matrix M
    printf("\n--- Initial Matrix M ---\n");
    float** M = createMatrix(graph_step1);
    displayMatrix(M, graph_step1->size);

    // 3. Calculate M^3
    printf("\n--- M^3 (Probability after 3 days) ---\n");
    float** M3 = matrixPower(M, graph_step1->size, 3);
    displayMatrix(M3, graph_step1->size);

    // 4. Calculate M^7
    printf("\n--- M^7 (Probability after 1 week) ---\n");
    float** M7 = matrixPower(M, graph_step1->size, 7);
    displayMatrix(M7, graph_step1->size);

    // 5. Calculate Convergence (M^n) until epsilon < 0.01
    printf("\n--- Convergence Analysis (Stationary Distribution) ---\n");
    float** M_prev = createZeroMatrix(graph_step1->size);
    float** M_curr = createZeroMatrix(graph_step1->size);
    copyMatrix(M, M_curr, graph_step1->size);

    float epsilon = 0.01;
    float diff = 1.0;
    int n = 1;

    while (diff > epsilon && n < 1000) {
        copyMatrix(M_curr, M_prev, graph_step1->size);

        float** temp = matrixMultiplication(M_prev, M, graph_step1->size);
        copyMatrix(temp, M_curr, graph_step1->size);
        freeMatrix(temp, graph_step1->size);

        diff = differenceMatrices(M_prev, M_curr, graph_step1->size);
        n++;
    }

    printf("Converged after %d steps with diff = %f\n", n, diff);
    printf("Limit Matrix (Stationary Distribution):\n");
    displayMatrix(M_curr, graph_step1->size);

    // free step 1
    freeMatrix(M, graph_step1->size);
    freeMatrix(M3, graph_step1->size);
    freeMatrix(M7, graph_step1->size);
    freeMatrix(M_prev, graph_step1->size);
    freeMatrix(M_curr, graph_step1->size);

    // PART 2 & 3: Tarjan, Submatrices, Periods (Complex Graph)
    printf("\n\n");

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
        printf("The period is : %d\n",getPeriod(submatrix,scc_partition->classes[i]->count));
        printf("\n");
        freeMatrix(submatrix, scc_partition->classes[i]->count);
    }
    freePartition(scc_partition);
    freeMatrix(matrix, graph->size);
    return 0;
}