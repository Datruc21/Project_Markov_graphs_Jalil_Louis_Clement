//
// Created by Louis on 10/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "hasse.h"

int main() {
    // Charger le graphe de l'exemple de validation
    //const char* filename = "../data/exemple_valid_step3.txt";
    const char* filename = "../data/exemple_hasse1.txt";

    t_adjacency_list* graph = readGraph(filename);

    if (graph == NULL) {
        return 1;
    }

    printf("--- Graph Loaded (%d vertices) ---\n", graph->size);
    displayAdjacencyList(graph);
    printf("\n");

    printf("--- Running Tarjan's Algorithm ---\n");
    t_partition* scc_partition = tarjanAlgorithm(*graph);

    printf("\n--- Validation of Step 1 (Part 2) ---\n");
    displayPartition(scc_partition);

    printf("\n--- Building Hasse Diagram (Step 2) ---\n");
    p_link_array links = makeHasseDiagram(graph);
    printf("%d links between classes (before removing redundancies).\n", links->log_size);
    removeTransitiveLinks(links);
    printf("%d links after removing redundancies.\n", links->log_size);

    // Mermaid
    char* mermaid_filename = "../data/hasse_diagram.txt";
    generateMermaidFile(mermaid_filename, scc_partition, links);

    // Step 3 (part 2)
    printf("\n--- Graph Characteristics (Step 3) ---\n");
    displayCharacteristics(scc_partition, links);

    // --- Nettoyage de la mémoire ---
    freePartition(scc_partition);

    return 0;
}