#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"


int main() {
    GRAPH *graph = NULL;
    graph = fill_graph(graph);
    dijkstra(graph);

    destroyGraph(graph);

    return 0;
}
