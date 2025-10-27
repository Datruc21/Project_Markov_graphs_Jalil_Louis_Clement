#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    // Step 1 : Create a graph
    t_adjacency_list* graph = readGraph("../data/exemple1.txt");

    printf("--- Validation of step 1 ---\n");
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

    return 0;
}