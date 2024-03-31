#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


void topSort(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt;
    int front = 0, rear = -1;
    int *queue = malloc(nodeCnt*sizeof(int));
    int *inDegree = calloc(nodeCnt , sizeof(int));

    for (int i = 0; i < nodeCnt; ++i)
        for (int j = 0; j < nodeCnt; ++j)
            if (graph->matrix[nodeCnt * i + j] != 0)
                inDegree[j]++;

    for (int i = 0; i < nodeCnt; ++i)
        if(inDegree[i] == 0)
            queue[++rear] = i;

    int index = 0;

    int *res = malloc(nodeCnt * sizeof(int));
    while (front <= rear) {
        res[index++] = queue[front++] + 1;
        for (int i = 0; i < nodeCnt; ++i) {
            if (graph->matrix[nodeCnt * queue[front - 1] + i]) {
                inDegree[i]--;
                if(inDegree[i] == 0)
                    queue[++rear] = i;
            }
        }
    }

    if (index != nodeCnt) {
        printf("impossible to sort\n");
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < nodeCnt; ++i)
        printf("%d ", res[i]);

    free(inDegree);
    free(res);
    free(queue);
}


int main() {
    GRAPH *graph = fill_graph();
    topSort(graph);
    destroyGraph(graph);
    return 0;
}
