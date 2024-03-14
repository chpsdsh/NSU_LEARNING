#include "kruskal.h"
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


KRUSKAL *createK(KRUSKAL *kruskal, int nodeCnt) {
    kruskal = malloc(sizeof(KRUSKAL));
    if (kruskal == NULL) {
        exit(EXIT_FAILURE);
    }
    kruskal->parent = malloc(nodeCnt * sizeof(int));
    kruskal->node = malloc(nodeCnt * sizeof(int));
    kruskal->rank = malloc(nodeCnt * sizeof(int));
    if (kruskal->parent == NULL || kruskal->node == NULL || kruskal->rank == NULL) {
        free(kruskal);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nodeCnt; ++i) {
        kruskal->node[i] = 0;
        kruskal->rank[i] = 0;
        kruskal->parent[i] = i;
    }
    return kruskal;
}


static int compare(const void *a, const void *b){
    const int *edge_a = a;
    const int *edge_b = b;
    return edge_a[2] - edge_b[2];
}


int findParent(int *parent, int i){
    if(parent[i] == i)
        return i;
    return parent[i] = findParent(parent, parent[i]);
}


void kruskal(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt, edgeCnt = graph->edgeCnt;

    KRUSKAL *kruskal = NULL;
    kruskal = createK(kruskal, nodeCnt);
    qsort(graph->weights, edgeCnt, sizeof(int) * 3, compare);
    for (int i = 0; i < edgeCnt; ++i) {
        int start = graph->weights[i * 3];
        int finish = graph->weights[i * 3 + 1];
        int fromSet = findParent(kruskal->parent, start);
        int toSet = findParent(kruskal->parent, finish);
        if (fromSet != toSet) {
            kruskal->node[start - 1] = 1;
            kruskal->node[finish - 1] = 1;
            if (kruskal->rank[fromSet] < kruskal->rank[toSet]) {
                int tmp = fromSet;
                fromSet = toSet;
                toSet = tmp;
            }
            kruskal->parent[toSet] = fromSet;
            if (kruskal->rank[fromSet] == kruskal->rank[toSet])
                ++(kruskal->rank)[fromSet];
        } else
            graph->weights[i * 3 + 2] = -1;
    }
    for (int i = 0; i < nodeCnt; ++i)
        if (!kruskal->node[i]) {
            destroyKruskal(kruskal);
            printf("no spanning tree");
            exit(0);
        }
    printResults(graph);

    destroyKruskal(kruskal);
}


void printResults(GRAPH *graph) {
    int edgeCnt = graph->edgeCnt;

    for (int i = 0; i < edgeCnt; ++i)
        if (graph->weights[i * 3 + 2] != -1)
            printf("%d %d \n", graph->weights[i * 3], graph->weights[i * 3 + 1]);
}

void destroyKruskal(KRUSKAL *kruskal){
    free(kruskal->node);
    free(kruskal->parent);
    free(kruskal->rank);
    free(kruskal);
}