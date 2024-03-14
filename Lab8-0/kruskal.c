#include <limits.h>
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
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nodeCnt; ++i) {
        kruskal->node[i] = 0;
        kruskal->rank[i] = 0;
        kruskal->parent[i] = i;
    }
    return kruskal;
}





void kruskal(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt, edgeCnt = graph->edgeCnt;

    KRUSKAL *kruskal = NULL;
    kruskal = createK(kruskal, nodeCnt);



    printResults(kruskal, graph);

    destroyKruskal(kruskal);
}


/*void printResults(KRUSKAL *kruskal, GRAPH *graph){
    int nodeCnt = graph->nodeCnt, start = graph->start, finish = graph->finish;
    for(int i = 0; i < nodeCnt; ++i){
        if(kruskal->visited[i]){
            if(kruskal->dist[i] > INT_MAX)
                printf("INT_MAX+ ");
            else
                printf("%lld ", kruskal->dist[i]);
        }
        else
            printf("oo ");
    }
    printf("\n");

    if(!kruskal->visited[finish - 1]){
        printf("no path \n");
        return;
    }
    int cntIntMax = 0;
    for (int i = 0; i < nodeCnt; ++i) {
        if (kruskal->dist[i]>= INT_MAX && kruskal->dist[i]!= LLONG_MAX)
            cntIntMax++;
    }
    if(cntIntMax > 2 && kruskal->dist[finish-1]>INT_MAX ){
        printf("overflow\n");
        return;
    }

    for (int i = finish - 1; i != start - 1; i = kruskal->way[i])
        printf("%d ", i + 1);
    printf("%d\n", start);
}
*/
void destroyKruskal(KRUSKAL *kruskal){
    free(kruskal->node);
    free(kruskal->parent);
    free(kruskal->rank);
    free(kruskal);
}