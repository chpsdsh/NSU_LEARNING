#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.h"
#include "prim.h"


PRIM *createP(PRIM *prim, int nodeCnt) {
    prim = malloc(sizeof(PRIM));
    if (prim == NULL) {
        exit(EXIT_SUCCESS);
    }
    prim->parent = malloc(nodeCnt * sizeof(int));
    prim->visited = malloc(nodeCnt * sizeof(int));
    prim->minedge = malloc(nodeCnt * sizeof(unsigned int));
    if (prim->parent == NULL || prim->visited == NULL || prim->minedge == NULL) {
        free(prim);
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < nodeCnt; ++i) {
        prim->visited[i] = 0;
        prim->minedge[i] = UINT_MAX;
    }
    prim->minedge[0] = 0;
    prim->parent[0] = -1;
    return prim;
}

int minEdge(PRIM*prim, GRAPH *graph){
    unsigned int min = UINT_MAX;
    int minInd;
    for (int i = 0; i < graph->nodeCnt; ++i)
        if (!prim->visited[i] && prim->minedge[i] < min)
            min = prim->minedge[i], minInd = i;
    return minInd;
}

void prim(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt;
    PRIM *prim = NULL;
    prim = createP(prim, nodeCnt);

    for (int cnt = 0; cnt < nodeCnt-1; ++cnt){
        int minInd = minEdge(prim,graph);
        prim->visited[minInd] = 1;
        for(int i = 0; i < graph->nodeCnt;++i){
            if (graph->weights[nodeCnt*minInd+i] && !prim->visited[i]
                && graph->weights[nodeCnt*minInd+i] < prim->minedge[i]){
                prim->parent[i] = minInd;
                prim->minedge[i] = graph->weights[nodeCnt*minInd+i];
            }
        }
    }
    for (int i = 0; i < nodeCnt; ++i){
        if (prim->minedge[i] == UINT_MAX) {
            destroyPrim(prim);
            printf("no spanning tree");
            exit(EXIT_SUCCESS);
        }
    }
    for (int i = 1; i < graph->nodeCnt; i++)
        printf("%d %d\n", prim->parent[i]+1, i+1);
    destroyPrim(prim);
}


void destroyPrim(PRIM *prim){
    if(prim){
        free(prim->visited);
        free(prim->parent);
        free(prim->minedge);
    }
    free(prim);
}