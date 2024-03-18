#ifndef NSU_LEARNING_GRAPH_H
#define NSU_LEARNING_GRAPH_H

typedef struct graph{
    int nodeCnt;
    int edgeCnt;
    int *weights;
}GRAPH;

GRAPH *create(GRAPH *graph, int nodeCnt);
GRAPH *fill_graph(GRAPH *graph);
void destroyGraph(GRAPH *graph);
#endif //NSU_LEARNING_GRAPH_H
