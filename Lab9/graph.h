#ifndef NSU_LEARNING_GRAPH_H
#define NSU_LEARNING_GRAPH_H
#include "dijkstra.h"
typedef struct graph{
    int nodeCnt;
    int start;
    int finish;
    int edgeCnt;
    int *weights;
}GRAPH;

GRAPH *create(GRAPH *graph, int nodeCnt);
GRAPH *fill_graph(GRAPH *graph);
void destroyGraph(GRAPH *graph);
void printResults(DIJKSTRA*dijkstra, GRAPH*graph);
void dijkstraAlgorithm(GRAPH* graph, int nodeCnt);
#endif //NSU_LEARNING_GRAPH_H
