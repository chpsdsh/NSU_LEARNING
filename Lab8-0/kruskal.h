
#ifndef NSU_LEARNING_KRUSKAL_H
#define NSU_LEARNING_KRUSKAL_H
#include "graph.h"

typedef struct kruskul{
    int *parent;
    int *node;
    int *rank;
}KRUSKAL;

KRUSKAL *createK(KRUSKAL *kruskal, int nodeCnt);
void kruskal(GRAPH *graph);
void printResults(KRUSKAL *kruskal,GRAPH *graph);
void destroyKruskal(KRUSKAL *kruskal);
#endif //NSU_LEARNING_DKRUSKAL_H
