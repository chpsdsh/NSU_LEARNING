#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


int max(int *array, int length){
    int max = -INT_MAX;
    for(int i = 0; i < length; i++)
        max = max < array[i] ? array[i] : max;
    return max;
}

void dfs(GRAPH* graph, int index,  STACK *stack) {
    graph->visited[index] = 1;
    for (int i = 0; i < graph->nodeCnt; ++i)
        if (graph->matrix[index * graph->nodeCnt + i] && !graph->visited[i])
            dfs(graph, i, stack);
    push(stack, index);
}

void paintingDfs(GRAPH* graph, int node, int colour) {
    graph->visited[node] = colour;
    for (int i = 0; i < graph->nodeCnt; ++i)
        if (graph->revmatrix[node * graph->nodeCnt + i] && !graph->visited[i])
            paintingDfs(graph, i, colour);
}

void printResults(GRAPH *graph){
    int maxComp = max(graph->visited, graph->nodeCnt);
    for (int i = 1; i < maxComp+1; i++) {
        printf("COMPONENT %d\n", i);
        for(int j = 0 ;j < graph->nodeCnt; j++)
            if(graph->visited[j] == i)
                printf("%d ", j+1);
        puts("");
    }
    destroyGraph(graph);
}

void kosaraju(GRAPH *graph){
    int node;
    int colour = 0;
    STACK *stack = createS();

    for(int i = 0; i < graph->nodeCnt; i++)
        if (!graph->visited[i])
            dfs(graph, i, stack);

    for(int i = 0; i < graph->nodeCnt; i++)
        graph->visited[i] = 0;

    while(!isEmpty(stack)){
        node = pop(stack);
        if(!graph->visited[node])
            paintingDfs(graph, node, ++colour);
    }

    printResults(graph);
    free(stack);
}

int main(){
    GRAPH *graph = fill_graph();
    kosaraju(graph);
    return 0;
}
