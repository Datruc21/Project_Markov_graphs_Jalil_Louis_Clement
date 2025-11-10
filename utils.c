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

/*
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
*/
void addCell(t_list* list, t_cell* cell) {
    if (cell != NULL) {
        cell->next = list->head;
        list->head = cell;
    }
}

void displayList(t_list* list) {
    printf("[head @]");
    t_cell* temp = list->head;
    while (temp != NULL) {
        printf("->");
        printf("(%d, %.2f)",temp->arrivalVertex,temp->probability);
        temp = temp->next;
    }
}

t_adjacency_list* createAdjacencyList(int size) {
    t_adjacency_list* adjacency_list = malloc(sizeof(t_adjacency_list));
    adjacency_list->size = size;
    adjacency_list->lists = malloc(sizeof(t_list*) * size);
    for (int i = 0; i < size; i++) {
        adjacency_list->lists[i] = createEmptyList();
    }
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
        fclose(file);
        exit(EXIT_FAILURE);
    }
    graph = createAdjacencyList(nbvert);

    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3)
    {
        addCell(graph->lists[start-1], createCell(end,proba));
        // we obtain, for each line of the file, the values
        // start, end and proba
        /*Add the edge that runs from 'start' to ‘end’ with the
        probability 'proba' to the adjacency list*/
    }
    fclose(file);
    return graph;
}

void isMarkovGraph(t_adjacency_list* adjacency_list) {
    int is_markov = 1;
    for (int i = 0; i < adjacency_list->size; i++) {
        float sum = 0.0f;
        t_cell* cell = adjacency_list->lists[i]->head;
        while (cell != NULL) {
            sum += cell->probability;
            cell = cell->next;
        }

        // Le sujet précise "entre 0.99 et 1", ce qui semble inclure 1.
        // La version de tes camarades excluait 1.0. Corrigons cela aussi.
        if (sum < 0.99 || sum > 1.0) {
            printf("The graph is not a Markov graph\n");
            printf("the sum of the probabilities of vertex %d is %.2f\n", i + 1, sum);
            is_markov = 0;
            break; // On a trouvé une erreur, on arrête la vérification.
        }
    }

    if (is_markov) {
        printf("The graph is a Markov graph\n");
    }
}

void representationGraph(t_adjacency_list* adjacency_list) {
    FILE* f;
    f = fopen("../data/Output.txt", "w");
    if (f == NULL) {
        printf("Error while writing the file!\n");
        return;
    } else {
        char parameters[100] = "---\nconfig:\n\tlayout: elk\n\ttheme: neo\n\tlook: neo\n---\n\nflowchart LR\n";
        fprintf(f, "%s", parameters);
        for (int i = 0; i < adjacency_list->size; i++) {
            fprintf(f,"%s((%d))\n",getID(i+1),i+1);
        }
        for (int i = 0; i < adjacency_list->size; i++) {
            t_cell* edges = adjacency_list->lists[i]->head;
            while (edges != NULL) {
                fprintf(f,"%s -->|%f|",getID(i+1),edges->probability);
                fprintf(f,"%s\n",getID(edges->arrivalVertex));
                edges = edges->next;
            }
        }
    }
}

t_tarjan_vertex** createTarjanVertexArray(t_adjacency_list T) {
    t_tarjan_vertex** vertex_array = (t_tarjan_vertex**)malloc(sizeof(t_tarjan_vertex*)*T.size);
    for (int i = 0; i<T.size; i++) {
        t_tarjan_vertex* vertex;
        vertex->id = T[i]->arrivalVertex;
        vertex->number = -1;
        vertex->link = -1;
        vertex->instack = 0;
        vertex_array[i] = vertex;
    }
    return vertex_array;
}

t_stack* createStack(int n) {
    t_stack* stack = (t_stack*)malloc(sizeof(t_stack)*n);
    stack->nb_vertices = 0;
    stack->size = n;
    return stack;
}

void pushStack(t_stack* stack, t_tarjan_vertex* vertex) {
    if (stack && stack->nb_vertices < stack->size) {
        stack[stack->nb_vertices] = vertex;
        stack->nb_vertices++;
        vertex->instack = 1;
    }
}

t_tarjan_vertex* popStack(t_stack* stack) {
    t_tarjan_vertex *vertex = stack->vertices[stack->nb_vertices];
    stack->nb_vertices--;
    vertex->instack = 0;
    return vertex;

}


void parcours(t_tarjan_vertex* v, int num, t_partition* classes, t_stack* stack){
    v->number = num;
    v->link = num;
    num++;
    pushStack(stack,v);
    v->instack = 1;


}

t_partition tarjanAlgorithm(t_adjacency_list adjacency_list) {
    int num = 0;
    t_stack stack = createStack();
    t_partition* result;


}