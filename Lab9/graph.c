#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

void errorCheck(int NodeCnt,int Start,int Finish,int EdgeCnt);

GRAPH *create(GRAPH *graph, int nodeCnt){
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

    if (start < 0 || start > nodeCnt || finish < 0 || finish > nodeCnt ){
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
        puts("bad number of edge");
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

        if (weight < 0 || weight > INT_MAX){
            puts("bad length");
            exit(0);
        }
        graph->weights[nodeCnt * (line-1) + (column-1)] = weight;
        graph->weights[nodeCnt*(column-1) + (line-1)] = weight;
    }

    return graph;
}


