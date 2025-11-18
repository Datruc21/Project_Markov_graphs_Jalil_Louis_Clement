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

struct s_tarjan_vertex {
    int id;
    int number;
    int link;
    int instack;
};
typedef struct s_tarjan_vertex t_tarjan_vertex;


struct s_class {
  int id;
  t_tarjan_vertex** vertices;
    int size;
    int count;
};
typedef struct s_class t_class;

struct s_partition {
    t_class** classes;
    int size;
    int count;
};
typedef struct s_partition t_partition;

struct s_stack{
    t_tarjan_vertex** vertices;
    int nb_vertices;
    int size;
};
typedef struct s_stack t_stack;

p_cell createCell(int arrivalVertex, float probability);
t_list* createEmptyList();
void addCell(t_list* list, t_cell* cell);
void displayList(t_list* list);
t_adjacency_list* createAdjacencyList(int size);
void displayAdjacencyList(t_adjacency_list* adjacency_list);
t_adjacency_list* readGraph(const char *filename);
void isMarkovGraph(t_adjacency_list* adjacency_list);
void representationGraph(t_adjacency_list* adjacency_list);
void displayPartition(t_partition* partition);

t_tarjan_vertex** createTarjanVertexArray(t_adjacency_list);
t_stack* createStack(int);
void pushStack(t_stack* stack, t_tarjan_vertex* vertex);
t_tarjan_vertex* popStack(t_stack* stack);
t_class* createClass(int size, int id);
t_partition* createPartition(int size);
t_partition* tarjanAlgorithm(t_adjacency_list adjacency_list);
void freePartition(t_partition* partition);
int isVertexInClass(p_cell vertex, t_class* class);


#endif