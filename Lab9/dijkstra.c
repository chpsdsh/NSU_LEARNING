
#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>


DIJKSTRA *createD(DIJKSTRA *dijkstra, int nodeCnt){
    dijkstra = malloc(sizeof(DIJKSTRA));
    dijkstra -> minDist = malloc(nodeCnt* sizeof(unsigned int));
    dijkstra-> visited = malloc(nodeCnt * sizeof(short int));
    dijkstra->way = malloc(nodeCnt* sizeof(short int));
    return dijkstra;
}

void destroyDijkstra(DIJKSTRA *dijkstra){
    free(dijkstra->minDist);
    free(dijkstra->visited);
    free(dijkstra->way);
}

int mindist(DIJKSTRA *dijkstra, int nodeCnt){
    int minIndex = -1;
    for (int j = 0; j < nodeCnt; j++){
        if(!(dijkstra->visited[j]) &&(minIndex==-1 || dijkstra->minDist[j] <= dijkstra->minDist[minIndex])){
            minIndex = j;
            printf("%d", minIndex);
        }

    }

    return minIndex;
}