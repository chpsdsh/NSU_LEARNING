#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include <limits.h>
GRAPH *create(GRAPH*graph, int edgeCnt) {
    graph = malloc(sizeof(GRAPH));
    if (graph == NULL) {
        exit(EXIT_FAILURE);
    }
    graph->weights = malloc(3 * edgeCnt * sizeof(int));
    if (graph->weights == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 3 * edgeCnt; ++i)
        graph->weights[i] = 0;
    return graph;
}

GRAPH *fill_graph(GRAPH *graph) {
    FILE *file = fopen("in.txt", "r");

    int nodeCnt;
    if (!fscanf(file, "%d", &nodeCnt)) {
        fclose(file);
        exit(0);
    }

    int edgeCnt;
    if (!fscanf(file, "%d", &edgeCnt)) {
        fclose(file);
        exit(0);
    }

    if (nodeCnt < 0 || nodeCnt > 5000) {
        puts("bad number of vertices");
        exit(0);
    }
    if (edgeCnt < 0 || edgeCnt > nodeCnt * (nodeCnt + 1) / 2) {
        puts("bad number of edges");
        exit(0);
    }
    graph = create(graph,nodeCnt);
    graph->nodeCnt = nodeCnt;
    graph->edgeCnt = edgeCnt;


    for (int i = 0; i < edgeCnt; ++i) {
        int start, finish;
        int weight;

        if (fscanf(file, "%d %d %d", &start, &finish, &weight) != 3) {
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (start < 1 || start > nodeCnt || finish < 1 || finish > nodeCnt) {
            puts("bad vertex");
            exit(0);
        }

        if (weight < 0 || weight > INT_MAX) {
            puts("bad length");
            exit(0);
        }
        graph->weights[3 * i] = start;
        graph->weights[3 * i +1] = finish;
        graph->weights[3 * i + 2] = weight;

    }

    fclose(file);
    return graph;
}


void destroyGraph(GRAPH *graph){
    free(graph->weights);
    free(graph);
}