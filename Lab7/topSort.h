
#ifndef NSU_LEARNING_TOPSORT_H
#define NSU_LEARNING_TOPSORT_H
#include "graph.h"

typedef struct topsort{
    int *inDegree;
    int *visited;
    int *res;
}TOPSORT;

int noDependencies(TOPSORT *topsort, int nodeCnt);
void destroyTopsort(TOPSORT*topsort);
TOPSORT *createT(TOPSORT *topsort, int nodeCnt);
void topSort(GRAPH *graph);
#endif //NSU_LEARNING_TOPSORT_H
