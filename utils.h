#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * @brief Node of a linked list representing a directed edge.
 */
struct s_cell{
    int arrivalVertex;  // Destination vertex ID
    float probability;  // Transition probability (weight)
    struct s_cell *next;
};
typedef struct s_cell t_cell;
typedef t_cell* p_cell;

/**
 * @brief Wrapper for a linked list of edges.
 */
struct s_list {
    t_cell* head;
};
typedef struct s_list t_list;

/**
 * @brief Adjacency list representation of the graph.
 * Stores an array of linked lists, where index i corresponds to vertex i.
 */
struct s_adjacency_list {
    int size;       // Number of vertices in the graph
    t_list** lists; // Array of pointers to lists
};
typedef struct s_adjacency_list t_adjacency_list;

/**
 * @brief Extended vertex structure used specifically for Tarjan's algorithm.
 */
struct s_tarjan_vertex {
    int id;       // Original ID of the vertex
    int number;   // Order of discovery (time)
    int link;     // Low-link value (smallest reachable index)
    int instack;  // Boolean flag (1 if in stack, 0 otherwise)
};
typedef struct s_tarjan_vertex t_tarjan_vertex;

/**
 * @brief Represents a Strongly Connected Component (SCC).
 */
struct s_class {
    int id;                     // ID of the class (C0, C1, etc.)
    t_tarjan_vertex** vertices; // Array of pointers to vertices belonging to this class
    int size;                   // Allocated capacity
    int count;                  // Actual number of vertices in this class
};
typedef struct s_class t_class;

/**
 * @brief Represents the partition of the graph into multiple classes.
 */
struct s_partition {
    t_class** classes; // Array of pointers to classes
    int size;          // Allocated capacity
    int count;         // Actual number of classes found
};
typedef struct s_partition t_partition;

/**
 * @brief Custom stack implementation for Tarjan's DFS traversal.
 */
struct s_stack{
    t_tarjan_vertex** vertices; // Array storing the stack elements
    int nb_vertices;            // Current number of elements
    int size;                   // Max capacity
};
typedef struct s_stack t_stack;

// --- Graph Construction Functions ---

/**
 * @brief Allocates and initializes a new edge cell.
 */
p_cell createCell(int arrivalVertex, float probability);

/**
 * @brief Allocates an empty linked list.
 */
t_list* createEmptyList();

/**
 * @brief Adds a cell to the head of a list.
 */
void addCell(t_list* list, t_cell* cell);

/**
 * @brief Prints the content of a single list (vertex neighbors).
 */
void displayList(t_list* list);

/**
 * @brief Initializes the main adjacency list structure.
 */
t_adjacency_list* createAdjacencyList(int size);

/**
 * @brief Displays the entire graph structure to the console.
 */
void displayAdjacencyList(t_adjacency_list* adjacency_list);

/**
 * @brief Reads graph data from a file and builds the adjacency list.
 * @param filename Path to the data file.
 * @return Pointer to the loaded graph.
 */
t_adjacency_list* readGraph(const char *filename);

/**
 * @brief Validates if the loaded graph respects Markov properties.
 * Checks if the sum of outgoing probabilities for each vertex is approx 1.0.
 */
void isMarkovGraph(t_adjacency_list* adjacency_list);

/**
 * @brief Generates a text file for graph visualization (Mermaid format).
 */
void representationGraph(t_adjacency_list* adjacency_list);

/**
 * @brief Displays the classes found by Tarjan's algorithm.
 */
void displayPartition(t_partition* partition);

// --- Tarjan's Algorithm Helper Functions ---

/**
 * @brief Initializes the array of Tarjan vertices based on the graph size.
 */
t_tarjan_vertex** createTarjanVertexArray(t_adjacency_list);

/**
 * @brief Creates the stack used for the DFS traversal.
 */
t_stack* createStack(int);

/**
 * @brief Pushes a vertex onto the stack.
 */
void pushStack(t_stack* stack, t_tarjan_vertex* vertex);

/**
 * @brief Pops the top vertex from the stack.
 */
t_tarjan_vertex* popStack(t_stack* stack);

/**
 * @brief Allocates memory for a new Class (SCC).
 */
t_class* createClass(int size, int id);

/**
 * @brief Allocates memory for the Partition structure.
 */
t_partition* createPartition(int size);

/**
 * @brief Executes Tarjan's algorithm to find Strongly Connected Components.
 * @param adjacency_list The graph to analyze.
 * @return The partition containing all found classes.
 */
t_partition* tarjanAlgorithm(t_adjacency_list adjacency_list);

/**
 * @brief Frees all memory associated with the partition and its classes.
 */
void freePartition(t_partition* partition);

/**
 * @brief Checks if a specific vertex belongs to a specific class.
 * Used during the construction of the Hasse diagram.
 */
int isVertexInClass(p_cell vertex, t_class* class);

/**
 * @brief Checks if a class index is valid within the partition.
 */
int doesClassExist (t_partition * part, int index);

#endif