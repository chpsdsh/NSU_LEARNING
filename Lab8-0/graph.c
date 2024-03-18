#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include <limits.h>

GRAPH *create(GRAPH*graph, int edgeCnt) {
    graph = malloc(sizeof(GRAPH));
    if (graph == NULL) {
        exit(EXIT_SUCCESS);
    }
    graph->weights = malloc(3 * edgeCnt * sizeof(int));
    if (graph->weights == NULL) {
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < 3 * edgeCnt; ++i)
        graph->weights[i] = 0;
    return graph;
}

GRAPH *fill_graph(GRAPH *graph) {
    FILE *file = fopen("in.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_SUCCESS);
    }

    int nodeCnt, edgeCnt;
    if (fscanf(file, "%d %d", &nodeCnt, &edgeCnt) != 2) {
        fclose(file);
        exit(EXIT_SUCCESS);
    }

    if (nodeCnt < 0 || nodeCnt > 5000) {
        puts("bad number of vertices");
        fclose(file);
        exit(EXIT_SUCCESS);
    }

    if (edgeCnt < 0 || edgeCnt > nodeCnt * (nodeCnt + 1) / 2) {
        puts("bad number of edges");
        fclose(file);
        exit(EXIT_SUCCESS);
    }

    if (edgeCnt == 0 && nodeCnt == 1) {
        fclose(file);
        exit(EXIT_SUCCESS);
    }
    if (edgeCnt == 0 && nodeCnt != 1) {
        fclose(file);
        puts("no spanning tree");
        exit(EXIT_SUCCESS);
    }
    graph = create(graph, edgeCnt);
    graph->nodeCnt = nodeCnt;
    graph->edgeCnt = edgeCnt;

    for (int i = 0; i < edgeCnt; ++i) {
        int start, finish;
        long long int weight;

        if (fscanf(file, "%d %d %lld", &start, &finish, &weight) != 3) {
            puts("bad number of lines");
            fclose(file);
            exit(EXIT_SUCCESS);
        }

        if (start < 1 || start > nodeCnt || finish < 1 || finish > nodeCnt) {
            puts("bad vertex");
            fclose(file);
            exit(EXIT_SUCCESS);
        }

        if (weight < 0 || weight > INT_MAX) {
            puts("bad length");
            fclose(file);
            exit(EXIT_SUCCESS);
        }

        graph->weights[3 * i] = start;
        graph->weights[3 * i + 1] = finish;
        graph->weights[3 * i + 2] = (int)weight;
    }
    fclose(file);
    return graph;
}


void destroyGraph(GRAPH *graph){
    if(graph){
        free(graph->weights);
    }
    free(graph);
}