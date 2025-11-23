#include <malloc.h>
#include "hasse.h"

p_link_array createLinkArray(int size) {
    p_link_array link_array = (p_link_array)malloc(sizeof(t_link_array));
    link_array->log_size = 0;
    link_array->links = malloc(sizeof(t_link*) * size);
    return link_array;
}

int isThereALink(p_link_array T,t_class* I, t_class* J) {
    for (int i = 0; i < T->log_size; i++) {
        if ((T->links[i]->start == I->id && T->links[i]->end == J->id) ||
            (T->links[i]->start == J->id && T->links[i]->end == I->id)) {
            return 1;
        }
    }
    return 0;
}

void freeLinkArray(t_link_array* link_array) {
    for (int i = 0; i < link_array->log_size; i++) {
        free(link_array->links[i]);
    }
    free(link_array->links);
    free(link_array);
}

t_link* createLink(int a, int b) {
    t_link* link = (t_link*)malloc(sizeof(t_link));
    link->start = a;
    link->end = b;
    return link;
}

p_link_array makeHasseDiagram(t_adjacency_list* T) {
    p_link_array link_array = createLinkArray(T->size);
    t_partition* partition = tarjanAlgorithm(*T);
    for (int i = 0; i<T->size; i++) {
        t_class* classI = NULL;
        for (int j = 0; j<partition->count; j++){
            for (int k = 0; k < partition->classes[j]->count; k++) {
                if (partition->classes[j]->vertices[k]->id == i) {
                    classI = partition->classes[j];
                    break;
                }
            }
            if (classI != NULL) break;
        }
        p_cell current = T->lists[i]->head;
        while (current != NULL) {
            t_class* classK = NULL;
            for (int j = 0 ;j<partition->count; j++) {
                if (isVertexInClass(current, partition->classes[j]))
                    classK = partition->classes[j];
            }
            if (classK != NULL && classK->id != classI->id) {
                if (!isThereALink(link_array,classI,classK)) {
                    link_array->links[link_array->log_size++] = createLink(classI->id, classK->id);
                }
            }
            current = current->next;
        }
    }
    return link_array;
}

void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link* link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < p_link_array->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link* link2 = p_link_array->links[j];
                if (link1->start == link2->start)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < p_link_array->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link* link3 = p_link_array->links[k];
                            if ((link3->start == link2->end) && (link3->end == link1->start))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}


void displayCharacteristics(t_partition* partition, t_link_array* links) {
    if (partition->count == 1) {
        printf("The graph is irreducible.\n");
    } else {
        printf("The graph is not irreducible.\n");
    }

    for (int i = 0; i < partition->count; i++) {
        t_class* curr = partition->classes[i];
        int is_persistent = 1;
        int j = 0;
        while (j < links->log_size && is_persistent) {
            if (links->links[j]->start == curr->id) {
                is_persistent = 0;
            }
            j++;
        }

        printf("\nClass C%d {", curr->id + 1);
        for (int k = 0; k < curr->count; k++) {
            printf("%d", curr->vertices[k]->id + 1);
            if (k < curr->count - 1) {
                printf(", ");
            }
        }
        printf("} is ");

        if (is_persistent) {
            printf("persistent.");
            if (curr->count == 1) {
                int absorbing_id = curr->vertices[0]->id;
                printf("  - State %d is absorbing.", absorbing_id + 1);
            }
        } else {
            printf("transitory.");
        }
    }
    printf("\n");
}

void generateMermaidFile(const char* filename, t_partition* partition, t_link_array* links) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        perror("Error opening file for Mermaid diagram");
        return;
    }

    fprintf(f, "flowchart LR\n\n");

    for (int i = 0; i < partition->count; i++) {
        t_class* current_class = partition->classes[i];
        fprintf(f, "    C%d[\"{", current_class->id);

        for (int j = 0; j < current_class->count; j++) {
            fprintf(f, "%d", current_class->vertices[j]->id + 1);
            if (j < current_class->count - 1) {
                fprintf(f, ", ");
            }
        }
        fprintf(f, "}\"]\n");
    }

    fprintf(f, "\n");

    for (int i = 0; i < links->log_size; i++) {
        t_link* link = links->links[i];
        fprintf(f, "    C%d --> C%d\n", link->start, link->end);
    }

    fclose(f);
    printf("Mermaid diagram generated in file: %s\n", filename);
}