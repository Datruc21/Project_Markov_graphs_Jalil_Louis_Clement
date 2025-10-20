#ifndef __UTILS_H__
#define __UTILS_H__

struct s_cell{
    int arrivalVertex;
    float probability;
    struct s_cell *next;
};
typedef struct s_cell t_cell;
typedef t_cell* p_cell;

struct s_list {
    t_cell* head;
};
typedef struct s_list t_list;

struct s_adjacency_list {
    int size;
    t_list** lists;
};
typedef struct s_adjacency_list t_adjacency_list;

p_cell createCell(int arrivalVertex, float probability);
t_list* createEmptyList();
void addCell(t_list* list, t_cell* cell);
void displayList(t_list* list);
t_adjacency_list* createAdjacencyList(int size);
void displayAdjacencyList(t_adjacency_list* adjacency_list);
t_adjacency_list* readGraph(const char *filename);
void isMarkovGraph(t_adjacency_list* adjacency_list);


#endif