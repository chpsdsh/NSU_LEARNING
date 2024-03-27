
#ifndef NSU_LEARNING_GRAPH_H
#define NSU_LEARNING_GRAPH_H
typedef struct graph {
    int nodeCnt;
    int edgeCnt;
    char *matrix;
} GRAPH;
void destroyGraph(GRAPH *graph);
GRAPH *fill_graph();
GRAPH *create(int nodeCnt);
#endif //NSU_LEARNING_GRAPH_H
