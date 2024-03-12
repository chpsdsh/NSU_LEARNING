#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

GRAPH *create(GRAPH*graph, int nodeCnt) {
    graph = malloc(sizeof(GRAPH));
    if (graph == NULL) {
        exit(EXIT_FAILURE);
    }
    graph->weights = malloc(nodeCnt * nodeCnt * sizeof(long int));
    if (graph->weights == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nodeCnt * nodeCnt; ++i)
        graph->weights[i] = 0;
    return graph;
}

GRAPH *fill_graph(GRAPH *graph) {
    FILE *file = fopen("in.txt", "r");
    int nodeCnt, start, finish;
    if (fscanf(file, "%d %d %d", &nodeCnt, &start, &finish) != 3) {
        fclose(file);
        exit(0);
    }

    if (start < 1 || start > nodeCnt || finish < 1 || finish > nodeCnt) {
        puts("bad vertex");
        exit(0);
    }

    int edgeCnt;
    if (fscanf(file, "%d", &edgeCnt) != 1) {
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
    graph->start = start;
    graph->finish = finish;


    for (int i = 0; i < edgeCnt; ++i) {
        int line, column;
        long long int weight;

        if (fscanf(file, "%d %d %lld", &line, &column, &weight) != 3) {
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (line < 1 || line > nodeCnt || column < 1 || column > nodeCnt) {
            puts("bad vertex");
            exit(0);
        }

        if (weight < 0 || weight > INT_MAX) {
            puts("bad length");
            exit(0);
        }
        graph->weights[nodeCnt * (line - 1) + (column - 1)] = weight;
        graph->weights[nodeCnt * (column - 1) + (line - 1)] = weight;
    }

    fclose(file);
    return graph;
}
void destroyGraph(GRAPH *graph){
    free(graph->weights);
    free(graph);
}