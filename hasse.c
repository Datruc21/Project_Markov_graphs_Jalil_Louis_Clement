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
        for (int j = 0 ;j<partition->count; j++){
            for (int k = 0; k < partition->classes[j]->count; k++) {
                if (partition->classes[j]->vertices[k]->id == i) {
                    classI = partition->classes[j];
                    break;
                }
            }
            if (classI != NULL) break;
        }
        p_cell current = T->lists[i]->head;//Now we must get through the others that are adjacent to it
        while (current != NULL) {
            t_class* classK = NULL;
            for (int j = 0 ;j<partition->count; j++) {
                if (isVertexInClass(current, partition->classes[j]))
                    classK = partition->classes[j];
            }
            if (classK != NULL && classK->id != classI->id) {//Put condition to compare classK and classI
                if (!isThereALink(link_array,classI,classK)) {//Put condition that link between classI and classK
                    //Add the link (Ci,Cj) to the structure that stores the links
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
}n


void displayCharacteristics(t_adjacency_list* T) {
    p_link_array link_array = makeHasseDiagram(T);
    t_partition* partition = tarjanAlgorithm(*T);
    int from = 0;
    int to = 0;
    if (partititon->count == 1) {
        printf("The graph is irreducible\n");
    }
    else {
        printf("The graph is not irreducible\n");
    }
    for (int i = 0; i<partition->count; i++) {
        int transitory = 0;
        int persistant = 0;
        int solo = 0;
        int absorbing = 0;
        if (partition->classes[i]->count == 1) {
            int solo = 1;
            //check if persistent
            for (int k = 0; k<link_array->log_size; k++) {
                if (link_array->links[k]->start == partition->classes[i]->vertices[0]->id &&
                    link_array->links[k]->end != partition->classes[i]->vertices[0]->id) {
                    absorbing = 0;
                }

            }
        }
        else {
        for (int j = 0; j<partition->classes[i]->count; j++) {
            //We look at each vertex
            //Need to iterate then all links, and check whether there are linked affecting it
            for (int k = 0; k<link_array->log_size; k++) {
                //Check transitory




                //check persistant




                //



            }
        }

        }
    }

}