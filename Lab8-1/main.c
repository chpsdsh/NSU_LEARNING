#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct graph{
    int nodeCnt;
    int edgeCnt;
    int *weights;
}GRAPH;

GRAPH *create(GRAPH*graph, int nodeCnt) {
    graph = malloc(sizeof(GRAPH));
    if (graph == NULL) {
        exit(EXIT_SUCCESS);
    }
    graph->weights = malloc(nodeCnt * nodeCnt * sizeof(int));
    if (graph->weights == NULL) {
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < nodeCnt * nodeCnt; ++i)
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
        puts("Error reading nodeCnt or edgeCnt");
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

typedef struct prim{
    int *parent;
    int *visited;
    int *key;
}PRIM;


void printResults(GRAPH *graph);
void destroyKruskal(PRIM *prim);


PRIM *createP(PRIM *prim, int nodeCnt) {
    prim = malloc(sizeof(PRIM));
    if (prim == NULL) {
        exit(EXIT_SUCCESS);
    }
    prim->parent = malloc(nodeCnt * sizeof(int));
    prim->visited = malloc(nodeCnt * sizeof(int));
    prim->key = malloc(nodeCnt * sizeof(int));
    if (prim->parent == NULL || prim->visited == NULL || prim->key == NULL) {
        free(prim);
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < nodeCnt; ++i) {
        prim->visited[i] = 0;
        prim->key[i] = LONG_MAX;
    }
    prim->key[0] = 0;
    prim->parent[0] = -1;
    return prim;
}

int minKey(PRIM*prim, GRAPH *graph){
    int min = LONG_MAX, minInd;
    for (int i; i < graph->nodeCnt; ++i)
        if (!prim->visited[i] && prim->key[i] < min)
            min = prim->key[i], minInd = i;
    return minInd;
}

void prim(GRAPH *graph) {
    int nodeCnt = graph->nodeCnt;
    PRIM *prim = NULL;
    prim = createP(prim, nodeCnt);
    int minInd = minKey(prim,graph);
    prim->visited[minInd] = 1;
    for(int i = 0; i < graph->nodeCnt;++i){
        if (graph->weights[nodeCnt*minInd+i] && !prim->visited[i]
        && graph->weights[nodeCnt*minInd+i] < prim->key[i])
            prim->parent[i] = minInd, prim->key[i] = graph->weights[nodeCnt*minInd+i];
    }

    printResults(graph);

    destroyKruskal(prim);
}


void printResults(GRAPH *graph) {
    int edgeCnt = graph->edgeCnt;

    for (int i = 0; i < edgeCnt; ++i)
        if (graph->weights[i * 3 + 2] != -1)
            printf("%d %d \n", graph->weights[i * 3], graph->weights[i * 3 + 1]);
}

void destroyKruskal(PRIM *prim){
    if(prim){
        free(prim->visited);
        free(prim->parent);
        free(prim->key);
    }
    free(prim);
}

int main() {
    GRAPH *graph = NULL;
    graph = fill_graph(graph);
    prim(graph);

    destroyGraph(graph);

    return 0;
}