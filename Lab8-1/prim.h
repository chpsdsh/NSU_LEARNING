#ifndef NSU_LEARNING_PRIM_H
#define NSU_LEARNING_PRIM_H
#include "graph.h"

typedef struct prim{
    int *parent;
    int *visited;
    unsigned int *minedge;
}PRIM;

void prim(GRAPH *graph);
void printResults(GRAPH *graph);
void destroyPrim(PRIM *prim);
#endif //NSU_LEARNING_PRIM_H
