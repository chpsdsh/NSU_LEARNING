#include "topSort.h"
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

TOPSORT *createT(TOPSORT *topsort, int nodeCnt) {
    topsort = malloc(sizeof(TOPSORT));
    if (topsort == NULL)
        exit(EXIT_SUCCESS);

    topsort->inDegree = calloc(nodeCnt , sizeof(int));
    topsort->visited = calloc(nodeCnt , sizeof(int));
    topsort->res = malloc(nodeCnt * sizeof(int));
    if (topsort->inDegree == NULL || topsort->visited == NULL || topsort->res == NULL) {
        free(topsort);
        exit(EXIT_SUCCESS);
    }
    return topsort;
}

int noDependencies(TOPSORT *topsort, int nodeCnt){
    for (int i = 0; i < nodeCnt; ++i)
        if (topsort->inDegree[i] == 0 && !topsort->visited[i])
            return i;
    return -1;
}

void topSort(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt;
    TOPSORT *topsort = NULL;
    topsort = createT(topsort, nodeCnt);

    for (int i = 0; i < nodeCnt; ++i)
        for (int j = 0; j < nodeCnt; ++j)
            if (graph->matrix[nodeCnt * i + j] != 0)
                topsort->inDegree[j]++;

    int index = 0;
    while (1) {
        int at = noDependencies(topsort, nodeCnt);
        if (at == -1)
            break;
        topsort->visited[at] = 1;
        topsort->res[index++] = at + 1;
        for (int i = 0; i < nodeCnt; ++i) {
            if (graph->matrix[nodeCnt * at + i]) {
                topsort->inDegree[i]--;
            }
        }
    }

    if (index != nodeCnt) {
        printf("impossible to sort\n");
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < nodeCnt; ++i) {
        printf("%d ", topsort->res[i]);
    }
    destroyTopsort(topsort);
}

void destroyTopsort(TOPSORT*topsort) {
    if (topsort) {
        free(topsort->inDegree);
        free(topsort->res);
        free(topsort->visited);
    }
    free(topsort);
}