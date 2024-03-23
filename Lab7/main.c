#include <stdlib.h>
#include <stdio.h>

typedef struct graph {
    int nodeCnt;
    int edgeCnt;
    char *matrix;
} GRAPH;

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

int noDependencies(int *in_degree, int nodeCnt, int *visited) {
    for (int i = 0; i < nodeCnt; ++i)
        if (in_degree[i] == 0 && !visited[i])
            return i;
    return -1;
}

void topSort(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt;
    int *in_degree = calloc(nodeCnt , sizeof(int));
    int *visited = calloc(nodeCnt, sizeof(int));


    for (int i = 0; i < nodeCnt; ++i)
        for (int j = 0; j < nodeCnt; ++j)
            if (graph->matrix[nodeCnt * i + j] != 0)
                in_degree[j]++;

    int *res = malloc(nodeCnt * sizeof(int));

    int index = 0;
    while (1) {
        int at = noDependencies(in_degree, nodeCnt, visited);
        if (at == -1)
            break;
        visited[at] = 1;
        res[index++] = at + 1;
        for (int i = 0; i < nodeCnt; ++i) {
            if (graph->matrix[nodeCnt * at + i]) {
                in_degree[i]--;
            }
        }
    }

    if (index != nodeCnt) {
        printf("impossible to sort\n");
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < nodeCnt; ++i) {
        printf("%d ", res[i]);
    }

    free(res);
    free(in_degree);
    free(visited);
}

void destroyGraph(GRAPH *graph) {
    if (graph) {
        free(graph->matrix);
    }
    free(graph);
}

int main() {
    GRAPH *graph = fill_graph();
    topSort(graph);
    destroyGraph(graph);
    return 0;
}
