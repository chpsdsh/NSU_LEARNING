#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


int minEdge(int *visited, unsigned int *minedge, GRAPH *graph){
    unsigned int min = UINT_MAX;
    int minInd;
    for (int i = 0; i < graph->nodeCnt; ++i)
        if (!visited[i] && minedge[i] < min)
            min = minedge[i], minInd = i;
    return minInd;
}


void prim(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt;

    int *visited = malloc(nodeCnt * sizeof(int));
    unsigned int* minedge = malloc(nodeCnt * sizeof(unsigned int));
    for (int i = 0; i < nodeCnt; ++i) {
        visited[i] = 0;
        minedge[i] = UINT_MAX;
    }

    minedge[0] = 0;
    int *parent = malloc(nodeCnt * sizeof(int));
    parent[0] = -1;
    for (int cnt = 0; cnt < nodeCnt-1; ++cnt){
        int minInd = minEdge(visited,minedge,graph);
        visited[minInd] = 1;
        for(int i = 0; i < graph->nodeCnt;++i){
            if (graph->weights[nodeCnt*minInd+i] && !visited[i]
                && graph->weights[nodeCnt*minInd+i] < minedge[i]){
                parent[i] = minInd;
                minedge[i] = graph->weights[nodeCnt*minInd+i];
            }
        }
    }
    for (int i = 0; i < nodeCnt; ++i)
        if (minedge[i] == UINT_MAX) {
            printf("no spanning tree");
            free(visited);
            free(parent);
            free(minedge);
            exit(EXIT_SUCCESS);
        }

    for (int i = 1; i < graph->nodeCnt; i++)
        printf("%d %d\n", parent[i]+1, i+1);

    free(visited);
    free(parent);
    free(minedge);
}


int main() {
    GRAPH *graph = NULL;
    graph = fill_graph(graph);
    prim(graph);
    destroyGraph(graph);
    return 0;
}