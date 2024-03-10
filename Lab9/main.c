#include <malloc.h>
#include <stdio.h>
#include "graph.h"


int main() {
    GRAPH *graph = NULL;
    graph = fill_graph(graph);
    dijkstraAlgorithm(graph, graph->nodeCnt);
    destroyGraph(graph);
}