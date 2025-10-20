#ifndef __UTILS_H__
#define __UTILS_H__

struct s_cell{
    int arrivalVertex;
    float probability;
    struct s_cell *next;
};
typedef struct s_cell t_cell;

struct s_list {
    t_cell* head;
};
typedef struct s_list t_list;

struct s_adjacency_list {
    int size;
    t_list* head;
};



#endif