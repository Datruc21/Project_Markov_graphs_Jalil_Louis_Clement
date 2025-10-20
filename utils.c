#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static char *getID(int i)
{
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';

    return buffer;
}

p_cell createCell(int arrivalVertex, float probability) {
    p_cell cell = malloc(sizeof(t_cell));
    cell->arrivalVertex = arrivalVertex;
    cell->probability = probability;
    cell->next = NULL;
    return cell;
}

t_list* createEmptyList() {
    t_list *list = malloc(sizeof(t_list));
    list->head = NULL;
    return list;
}

void addCell(t_list* list, t_cell* cell) {
    if (list->head == NULL) {
        list->head = cell;
    }
    else {
        t_cell* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = cell;
    }
}

void displayList(t_list* list) {
    printf("[head @]");
    t_cell* temp = list->head;
    while (temp->next != NULL) {
        printf("->");
        printf("(%d, %f)",temp->arrivalVertex,temp->probability);
        temp = temp->next;
    }
}

t_adjacency_list* createAdjacencyList(int size) {
    t_adjacency_list* adjacency_list = malloc(sizeof(t_adjacency_list));
    adjacency_list->size = size;
    adjacency_list->lists = malloc(sizeof(t_list*) * size);
    return adjacency_list;
}

void displayAdjacencyList(t_adjacency_list* adjacency_list) {
    for (int i = 0; i < adjacency_list->size; i++) {
        printf("List for vertex %d : ",i+1);
        t_list* line = adjacency_list->lists[i];
        displayList(line);
        printf("\n");
    }
}

t_adjacency_list* readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, start, end;
    float proba;
    //declare the variable for the adjacency list
    t_adjacency_list* graph;
    if (file == NULL)
    {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1)
    {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    graph = createAdjacencyList(nbvert);
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3)
    {
        // we obtain, for each line of the file, the values
        // start, end and proba
        /*Add the edge that runs from 'start' to ‘end’ with the
        probability 'proba' to the adjacency list*/

        }
    fclose(file);
    return graph;
}


/*for nbvertices time
 *store first occurence of a certain vertices
