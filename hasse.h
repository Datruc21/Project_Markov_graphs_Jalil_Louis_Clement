#include <stdio.h>
#include "utils.h"
#ifndef __HASSE_H__
#define __HASSE_H__

/**
 * @brief Represents a directed edge between two classes (Strongly Connected Components).
 */
struct s_link {
    int start; // ID of the source class
    int end;   // ID of the destination class
};
typedef struct s_link t_link;

/**
 * @brief Dynamic array structure to store multiple links.
 */
struct s_link_array {
    int log_size;   // Current number of links stored
    t_link** links; // Array of pointers to links
};

typedef struct s_link_array t_link_array;
typedef struct s_link_array* p_link_array;

/**
 * @brief Allocates memory for a link array structure.
 * @param size The maximum capacity of the array.
 * @return A pointer to the initialized link array.
 */
p_link_array createLinkArray(int size);

/**
 * @brief Constructs the initial diagram showing connections between classes.
 * Runs Tarjan's algorithm and identifies edges that go from one class to a different one.
 * @param T Pointer to the graph's adjacency list.
 * @return A link array representing the edges between classes.
 */
p_link_array makeHasseDiagram(t_adjacency_list* T);

/**
 * @brief Removes redundant edges to create a proper Hasse diagram.
 * If A->B and B->C exist, the direct link A->C is considered transitive and removed.
 * @param p_link_array Pointer to the link array to optimize.
 */
void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Generates a text file with Mermaid syntax to visualize the graph partition.
 * @param filename The output file path.
 * @param partition The partition containing the classes (nodes).
 * @param links The link array representing the connections (edges).
 */
void generateMermaidFile(const char* filename, t_partition* partition, t_link_array* links);

/**
 * @brief Analyzes and prints the topological properties of the graph.
 * Determines if the graph is irreducible and identifies transient, persistent,
 * and absorbing classes based on the Hasse diagram.
 * @param partition The partition of the graph.
 * @param links The Hasse diagram links.
 */
void displayCharacteristics(t_partition* partition, t_link_array* links);

#endif