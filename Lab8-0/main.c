#include <stdio.h>
#include "graph.h"
#include "kruskal.h"


int main() {
    GRAPH *graph = NULL;
    graph = fill_graph(graph);
    kruskal(graph);

    destroyGraph(graph);

    return 0;
}
