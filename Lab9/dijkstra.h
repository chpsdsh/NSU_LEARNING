

#ifndef NSU_LEARNING_DIJKSTRA_H
#define NSU_LEARNING_DIJKSTRA_H

typedef struct dijkstra{
    int *visited;
    int *minDist;
    int *way;
}DIJKSTRA;

DIJKSTRA *createD(DIJKSTRA *dijkstra, int nodeCnt);
void destroyDijkstra(DIJKSTRA *dijkstra);
int mindist(DIJKSTRA *dijkstra, int nodeCnt);


#endif //NSU_LEARNING_DIJKSTRA_H
