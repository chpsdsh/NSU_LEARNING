
#ifndef NSU_LEARNING_DIJKSTRA_H
#define NSU_LEARNING_DIJKSTRA_H
#include "graph.h"

typedef struct dijkstra{
    int *visited;
    long long int *dist;
    int *way;
}DIJKSTRA;

DIJKSTRA *createD(DIJKSTRA *dijkstra, int nodeCnt);
int minDistance(int nodeCnt, DIJKSTRA *dijkstra);
void dijkstra(GRAPH *graph);
void printResults(DIJKSTRA *dijkstra,GRAPH *graph);
void destroyDijkstra(DIJKSTRA *dijkstra);
#endif //NSU_LEARNING_DIJKSTRA_H
