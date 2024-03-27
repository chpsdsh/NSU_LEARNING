#include "graph.h"
#include "topSort.h"


int main() {
    GRAPH *graph = fill_graph();
    topSort(graph);
    destroyGraph(graph);
    return 0;
}
