#ifndef NSU_LEARNING_GRAPH_H
#define NSU_LEARNING_GRAPH_H

typedef struct graph{
    int nodeCnt;
    int edgeCnt;
    int *weights;
}GRAPH;

void destroyGraph(GRAPH *graph);
GRAPH *fill_graph(GRAPH *graph);
GRAPH *create(GRAPH*graph, int nodeCnt);
#endif //NSU_LEARNING_GRAPH_H
