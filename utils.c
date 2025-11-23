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

// creates a t_cell which is an edge of the graph
p_cell createCell(int arrivalVertex, float probability) {
    p_cell cell = malloc(sizeof(t_cell));
    cell->arrivalVertex = arrivalVertex;
    cell->probability = probability;
    cell->next = NULL;
    return cell;
}

// creates an empty linked list that will contain every outgoing edges of one vertex
t_list* createEmptyList() {
    t_list *list = (t_list*)malloc(sizeof(t_list));
    list->head = NULL;
    return list;
}

// adds a t_cell at the head of the linked list (complexity O(1))
void addCell(t_list* list, t_cell* cell) {
    if (cell != NULL) {
        cell->next = list->head;
        list->head = cell;
    }
}

// displays the linked list of a vertex with the visual format asked
void displayList(t_list* list) {
    printf("[head @]");
    t_cell* temp = list->head;
    while (temp != NULL) {
        printf("->");
        printf("(%d, %.2f)",temp->arrivalVertex,temp->probability);
        temp = temp->next;
    }
}

// creates the adjacency list (an array containing the t_list of every vertex)
t_adjacency_list* createAdjacencyList(int size) {
    t_adjacency_list* adjacency_list = malloc(sizeof(t_adjacency_list));
    adjacency_list->size = size;
    adjacency_list->lists = malloc(sizeof(t_list*) * size);
    for (int i = 0; i < size; i++) {
        adjacency_list->lists[i] = createEmptyList();
    }
    return adjacency_list;
}

// displays the adjacency list
void displayAdjacencyList(t_adjacency_list* adjacency_list) {
    for (int i = 0; i < adjacency_list->size; i++) {
        printf("List for vertex %d : ",i+1);
        t_list* line = adjacency_list->lists[i];
        displayList(line);
        printf("\n");
    }
}

// creates the adjacency list of a graph by reading the graph from a text file
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

// checks if the graph given is a markov graph (the sum of all probabilities equals to 1)
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

// generates the mermaid syntax to visualize the graph and write it into a text file ("../data/Output.txt")
void representationGraph(t_adjacency_list* adjacency_list) {
    FILE* f;
    f = fopen("../data/Output.txt", "w");
    if (f == NULL) {
        printf("Error while writing the file!\n");
        return;
    } else {
        char parameters[100] = "---\nconfig:\nlayout: elk\ntheme: neo\nlook: neo\n---\n\nflowchart LR\n";
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
        t_tarjan_vertex* vertex = (t_tarjan_vertex*)malloc(sizeof(t_tarjan_vertex));
        vertex->id = i;
        vertex->number = -1;
        vertex->link = -1;
        vertex->instack = 0;
        vertex_array[i] = vertex;
    }
    return vertex_array;
}

t_stack* createStack(int n) {
    t_stack* stack = (t_stack*)malloc(sizeof(t_stack)*n);
    stack->vertices = (t_tarjan_vertex**)malloc(sizeof(t_tarjan_vertex*)*n);
    stack->nb_vertices = 0;
    stack->size = n;
    return stack;
}


void pushStack(t_stack* stack, t_tarjan_vertex* vertex) {
    if (stack && stack->nb_vertices < stack->size) {
        stack->vertices[stack->nb_vertices] = vertex;
        stack->nb_vertices++;
    }
}

t_tarjan_vertex* popStack(t_stack* stack) {
    if (stack && stack->nb_vertices > 0) {
        stack->nb_vertices--;
        t_tarjan_vertex *vertex = stack->vertices[stack->nb_vertices];
        return vertex;
    }
    return NULL;
}

t_class* createClass(int size, int id) {
    t_class* cls = malloc(sizeof(t_class)*size);
    cls->id = id;
    cls->size = size;
    cls->vertices = malloc(sizeof(t_tarjan_vertex*)*size);
    cls->count = 0;
    return cls;
}

t_partition* createPartition(int size) {
    t_partition* partition = (t_partition*)malloc(sizeof(t_partition)*size);
    partition->size = size;
    partition->classes = (t_class**)malloc(sizeof(t_class*)*size);
    partition->count = 0;
    return partition;
}

int min(int a,int b) {
    if (a > b) {
        return b;
    }
    return a;
}


void parcours(t_tarjan_vertex** array, t_tarjan_vertex* v, int* num, t_partition* partition, t_stack* stack, t_adjacency_list T, int* id) {
    v->number = *num;
    v->link = *num;
    *num = *num + 1;
    pushStack(stack,v);
    v->instack = 1;
    //Go through v->successors (linked list) and check each time number arrivalVertex with the other tarjans ids
    t_list* successors = T.lists[v->id];
    p_cell cell = successors->head;
    while (cell != NULL) {
        int index = cell->arrivalVertex - 1; //added -1 here as normal vertex are indexed from 1, while tranjan ones from 0
        t_tarjan_vertex* w = array[index];
        if (w->number == -1) {
            // Mise à jour de l'appel récursif (ajout de id)
            parcours(array, w, num, partition, stack, T, id);
            v->link = min(v->link, w->link);
        }
        else if (w->instack == 1) {
            v->link = min(v->link, w->number);
        }
        cell = cell->next;
    }
    if (v->number == v->link) {
        //Create an empty class

        // Attribution de l'ID courant à la classe et incrémentation
        t_class* class = createClass(T.size, *id);
        (*id)++; // Incrémentation de l'ID pour la prochaine classe

        t_tarjan_vertex* w;
        do {
            w = popStack(stack);
            w->instack = 0;
            class->vertices[class->count++] = w;
        } while (w != v);

        //add class to partition
        partition->classes[partition->count++] = class;
    }
}

t_partition* tarjanAlgorithm(t_adjacency_list adjacency_list) {
    int num = 0;
    int class_id = 0;

    t_stack* stack = createStack(adjacency_list.size + 1);
    t_partition* result = createPartition(adjacency_list.size);
    t_tarjan_vertex** vertices = createTarjanVertexArray(adjacency_list);
    for (int i = 0; i < adjacency_list.size; i++) {
        if (vertices[i]->number == -1)
                parcours(vertices, vertices[i], &num, result, stack, adjacency_list, &class_id);
    }
    free(stack->vertices);
    free(stack);
    return result;
}

// Fonction pour afficher le résultat
void displayPartition(t_partition* partition) {
    printf("Found %d strongly connected components:\n", partition->count);
    for (int i = 0; i < partition->count; i++) {
        printf("%d Component C%d: {", partition->classes[i]->id ,i + 1);
        for (int j = 0; j < partition->classes[i]->count; j++) {
            printf("%d", partition->classes[i]->vertices[j]->id + 1);
            if (j < partition->classes[i]->count - 1) {
                printf(",");
            }
        }
        printf("}\n");
    }
}

void freePartition(t_partition* partition) {
    if (partition == NULL) {
        return;
    }

    // 1. Libérer chaque classe individuellement
    for (int i = 0; i < partition->count; i++) {
        if (partition->classes[i] != NULL) {
            // 1a. Libérer le tableau de sommets de la classe
            free(partition->classes[i]->vertices);
            // 1b. Libérer la structure de la classe elle-même
            free(partition->classes[i]);
        }
    }

    // 2. Libérer le tableau de pointeurs vers les classes
    free(partition->classes);

    // 3. Libérer la structure de partition elle-même
    free(partition);
}

int isVertexInClass(p_cell vertex, t_class* class) {
    //Checks if a vertex is in the class
    for (int i = 0; i<class->count; i++) {
        if (vertex->arrivalVertex - 1  == class->vertices[i]->id)
            return 1;
    }
    return 0;
}


int doesClassExist (t_partition * part, int index) {
    if ((index < 0) || ( part->count) <= index) {
        return 0;
    }
    return 1;
}
