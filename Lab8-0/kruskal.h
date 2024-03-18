
#ifndef NSU_LEARNING_KRUSKAL_H
#define NSU_LEARNING_KRUSKAL_H
#include "graph.h"

typedef struct kruskul{
    int *parent;
    int *visited;
    int *rank;
}KRUSKAL;

KRUSKAL *createK(KRUSKAL *kruskal, int nodeCnt);
void kruskal(GRAPH *graph);
int findParent(int *parent, int i);
static int compare(const void *a, const void *b);
void printResults(GRAPH *graph);
void destroyKruskal(KRUSKAL *kruskal);
#endif //NSU_LEARNING_KRUSKAL_H
