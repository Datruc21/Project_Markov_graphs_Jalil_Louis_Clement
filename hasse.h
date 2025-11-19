#include <stdio.h>
#include "utils.h"
#ifndef __HASSE_H__
#define __HASSE_H__

struct s_link {
    int start;
    int end;
};
typedef struct s_link t_link;


struct s_link_array {
    int log_size;
    t_link** links;
};


typedef struct s_link_array t_link_array;
typedef struct s_link_array* p_link_array;

p_link_array createLinkArray(int size);
p_link_array makeHasseDiagram(t_adjacency_list* T);
void removeTransitiveLinks(t_link_array *p_link_array);
void displayCharacteristics(t_adjacency_list* T);
void generateMermaidFile(const char* filename, t_partition* partition, t_link_array* links);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif