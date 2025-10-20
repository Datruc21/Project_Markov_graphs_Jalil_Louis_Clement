#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

int main() {
    displayAdjacencyList(readGraph("../data/exemple1.txt"));
    return 0;
}
