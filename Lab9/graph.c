#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"

GRAPH *create(GRAPH *graph, int nodeCnt){
    graph = malloc(sizeof(GRAPH));
    graph -> weights = malloc(nodeCnt * nodeCnt * sizeof(unsigned int));
    graph->edgeCnt = nodeCnt;
    return graph;
}

GRAPH *fill_graph(GRAPH *graph){
    FILE *file = fopen("in.txt", "r");
    int nodeCnt;
    if(!fscanf(file, "%d", &nodeCnt)){
        fclose(file);
        return 0;
    }
    int start, finish;
    if(fscanf(file, "%d %d", &start,&finish)!=2){
        fclose(file);
        return 0;
    }

    if (start < 1 || start > nodeCnt || finish < 1 || finish > nodeCnt ){
        puts("bad vertex");
        exit(0);
    }

    int edgeCnt;
    if(!fscanf(file, "%d", &edgeCnt)){
        fclose(file);
        return 0;
    }

    if (nodeCnt < 0 || nodeCnt > 5000){
        puts("bad number of vertices");
        exit(0);
    }
    if (edgeCnt < 0 || edgeCnt > nodeCnt*(nodeCnt+1)/2){
        puts("bad number of edges");
        exit(0);
    }

    graph = create(graph,nodeCnt);
    graph->nodeCnt = nodeCnt;
    graph->edgeCnt = edgeCnt;
    graph->start = start;
    graph->finish = finish;
    for(int i = 0; i < edgeCnt; ++i){
        int line, column, weight;
        if(fscanf(file, "%d %d %d", &line,&column,&weight)!=3){
            fclose(file);
            puts("bad number of lines");
            return 0;
        }

        if (start < 0 || start > nodeCnt || finish < 0 || finish > nodeCnt ){
            puts("bad vertex");
            exit(0);
        }

        if (weight <= 0 || weight > INT_MAX){
            puts("bad length");
            exit(0);
        }
        graph->weights[nodeCnt * (line-1) + (column-1)] = weight;
        graph->weights[nodeCnt*(column-1) + (line-1)] = weight;
    }
    return graph;
}

void dijkstraAlgorithm(GRAPH* graph, int nodeCnt){
    DIJKSTRA *dijkstra = NULL;
    dijkstra = createD(dijkstra, nodeCnt);
    for(int i = 0; i < nodeCnt; i++){
        dijkstra->visited[i] = 0;
        dijkstra->minDist[i] = UINT_MAX;
    }
    dijkstra->minDist[graph->start - 1] = 0;
    for(int i = 0; i < nodeCnt; i++){
        int minIndex;
        unsigned int min = UINT_MAX;
        for (int j = 0; j < nodeCnt; j++){
            if(!(dijkstra->visited[j]) && dijkstra->minDist[j] <= min){
                minIndex = j;
                min = dijkstra->minDist[j];

            }

        }
        if(dijkstra->minDist[minIndex] == UINT_MAX){
            printResults(dijkstra,graph);
            destroyDijkstra(dijkstra);
            return;
        }
        dijkstra->visited[minIndex] = 1;

        for(int k = 0; k < nodeCnt; k++){
            if (!dijkstra->visited[k] && graph->weights[nodeCnt*minIndex+k]
            && dijkstra->minDist[minIndex] != UINT_MAX
            && dijkstra->minDist[minIndex] + graph->weights[nodeCnt*minIndex+k] < dijkstra->minDist[k])
                dijkstra->minDist[k] = dijkstra->minDist[minIndex] + graph->weights[nodeCnt * minIndex + k];
            dijkstra->way[k] = minIndex;
        }
    }
    printResults(dijkstra,graph);
    destroyDijkstra(dijkstra);
}

void printResults(DIJKSTRA*dijkstra, GRAPH*graph){
    for(int i = 0; i < graph->nodeCnt; ++i){
        if(dijkstra->visited[i]){
            if(dijkstra->minDist[i] > INT_MAX)
                printf("INT_MAX+ ");
            else
                printf("%u ", dijkstra->minDist[i]);
        }
        else
            printf("oo ");
    }
    printf("\n");
    if(!dijkstra->visited[graph->finish - 1]){
        printf("no path \n");
        return;
    }
    int cntIntMax = 0;
    for(int i = 0; i < graph->nodeCnt; ++i){
        if(dijkstra->minDist[i] > INT_MAX)
            cntIntMax++;
    }
    if(cntIntMax >= 2){
        printf("overflow\n");
        return;
    }
    for (int i = graph->finish - 1; i != graph->start - 1; i = dijkstra->way[i])
        printf("%d ", i + 1);
    printf("%d\n", graph->start);

}

void destroyGraph(GRAPH *graph){
    free(graph->weights);
}
