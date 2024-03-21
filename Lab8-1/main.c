#include <stdlib.h>
#include "graph.h"
#include "prim.h"


int main() {
    GRAPH *graph = NULL;
    graph = fill_graph(graph);
    prim(graph);
    destroyGraph(graph);
    return 0;
}