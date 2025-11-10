//
// Created by Louis on 10/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    // Charger le graphe de l'exemple de validation
    const char* filename = "../data/exemple_valid_step3.txt"; // Assure-toi que le chemin est correct
    t_adjacency_list* graph = readGraph(filename);

    if (graph == NULL) {
        return 1;
    }

    printf("--- Graph Loaded (%d vertices) ---\n", graph->size);
    displayAdjacencyList(graph); // Commenter pour voir la liste d'adjacence
    printf("\n");

    printf("--- Running Tarjan's Algorithm ---\n");
    t_partition* scc_partition = tarjanAlgorithm(*graph);

    printf("\n--- Validation of Step 1 (Part 2) ---\n");
    displayPartition(scc_partition);

    // A faire : Libérer la mémoire allouée pour la partition et le graphe !
    // ... code de libération de mémoire ...

    return 0;
}