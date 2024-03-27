#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

GRAPH *create(int nodeCnt) {
    GRAPH *graph = malloc(sizeof(GRAPH));
    if (graph == NULL)
        exit(EXIT_SUCCESS);

    graph->matrix = malloc(nodeCnt * nodeCnt * sizeof(char));

    if (graph->matrix == NULL) {
        free(graph);
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < nodeCnt * nodeCnt; i++)
        graph->matrix[i] = 0;

    return graph;
}

GRAPH *fill_graph() {
    FILE *file = fopen("in.txt", "r");
    if (!file) {
        exit(EXIT_SUCCESS);
    }

    int nodeCnt, edgeCnt;
    if (fscanf(file, "%d %d", &nodeCnt, &edgeCnt) != 2) {
        puts("bad number of lines");
        fclose(file);
        exit(EXIT_SUCCESS);
    }

    if (nodeCnt < 0 || nodeCnt > 2000) {
        puts("bad number of vertices");
        fclose(file);
        exit(EXIT_SUCCESS);
    }
    if (edgeCnt < 0 || edgeCnt > nodeCnt * (nodeCnt + 1) / 2) {
        puts("bad number of edges");
        fclose(file);
        exit(EXIT_SUCCESS);
    }

    GRAPH *graph = create(nodeCnt);
    graph->nodeCnt = nodeCnt;
    graph->edgeCnt = edgeCnt;

    for (int i = 0; i < edgeCnt; ++i) {
        int start, finish;

        if (fscanf(file, "%d %d", &start, &finish) != 2) {
            puts("bad number of lines");
            fclose(file);
            exit(EXIT_SUCCESS);
        }

        if (start < 1 || start > nodeCnt || finish < 1 || finish > nodeCnt) {
            puts("bad vertex");
            fclose(file);
            exit(EXIT_SUCCESS);
        }

        graph->matrix[nodeCnt * (start - 1) + (finish - 1)] = 1;
    }

    fclose(file);
    return graph;
}

void destroyGraph(GRAPH *graph) {
    if (graph) {
        free(graph->matrix);
    }
    free(graph);
}