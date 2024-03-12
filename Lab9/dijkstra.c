#include <limits.h>
#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


DIJKSTRA *createD(DIJKSTRA *dijkstra, int nodeCnt) {
    dijkstra = malloc(sizeof(DIJKSTRA));
    if (dijkstra == NULL) {
        exit(EXIT_FAILURE);
    }
    dijkstra->dist = malloc(nodeCnt * sizeof(long long int));
    dijkstra->visited = malloc(nodeCnt * sizeof(int));
    dijkstra->way = malloc(nodeCnt * sizeof(int));
    if (dijkstra->dist == NULL || dijkstra->visited == NULL || dijkstra->way == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nodeCnt; ++i) {
        dijkstra->dist[i] = LLONG_MAX;
        dijkstra->visited[i] = 0;
    }
    return dijkstra;
}


int minDistance(int nodeCnt, DIJKSTRA *dijkstra) {
    long long int min = LLONG_MAX;
    int min_index;

    for (int v = 0; v < nodeCnt; ++v)
        if (dijkstra->visited[v] == 0 && dijkstra->dist[v] < min)
            min = dijkstra->dist[v], min_index = v;

    return min_index;
}


void dijkstra(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt, start = graph->start;

    DIJKSTRA *dijkstra = NULL;
    dijkstra = createD(dijkstra, nodeCnt);

    dijkstra->dist[start - 1] = 0;

    for (int count = 0; count < nodeCnt; ++count) {
        int minindex = minDistance(nodeCnt, dijkstra);
        dijkstra->visited[minindex] = 1;
        for (int v = 0; v < nodeCnt; v++) {
            if (! dijkstra->visited[v] && graph->weights[nodeCnt * minindex + v] &&
                dijkstra->dist[minindex] != LLONG_MAX &&
                dijkstra->dist[minindex] + graph->weights[nodeCnt * minindex + v] < dijkstra->dist[v]) {
                dijkstra->dist[v] =  dijkstra->dist[minindex] + graph->weights[nodeCnt * minindex + v];
                dijkstra->way[v] = minindex;
            }
        }
    }

    printResults(dijkstra, graph);

    destroyDijkstra(dijkstra);
}


void printResults(DIJKSTRA *dijkstra, GRAPH *graph){
    int nodeCnt = graph->nodeCnt, start = graph->start, finish = graph->finish;
    for(int i = 0; i < nodeCnt; ++i){
        if(dijkstra->visited[i]){
            if(dijkstra->dist[i] > INT_MAX)
                printf("INT_MAX+ ");
            else
                printf("%lld ", dijkstra->dist[i]);
        }
        else
            printf("oo ");
    }
    printf("\n");

    if(!dijkstra->visited[finish - 1]){
        printf("no path \n");
        return;
    }
    int cntIntMax = 0;
    for (int i = 0; i < nodeCnt; ++i) {
        if (dijkstra->dist[i]>= INT_MAX && dijkstra->dist[i]!= LLONG_MAX)
            cntIntMax++;
    }
    if(cntIntMax > 2 && dijkstra->dist[finish-1]>INT_MAX ){
        printf("overflow\n");
        return;
    }

    for (int i = finish - 1; i != start - 1; i = dijkstra->way[i])
        printf("%d ", i + 1);
    printf("%d\n", start);
}

void destroyDijkstra(DIJKSTRA *dijkstra){
    free(dijkstra->dist);
    free(dijkstra->visited);
    free(dijkstra->way);
    free(dijkstra);
}