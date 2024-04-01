#include "graph.h"
#include "stack.h"

void dfs(GRAPH* graph, int index,  STACK *stack) {

    graph->visited[index] = 1;
    for (int i = 0; i < graph->nodeCnt; ++i) {
        if (graph->matrix[index * graph->nodeCnt + i] && !graph->visited[i]) {
            dfs(graph, i,  stack);
        }
        push(stack, index);
    }
}

void kosaraju(GRAPH *graph){

    STACK *stack = createS();

    int nodeCnt = graph->nodeCnt;
    for(int i = 0; i < nodeCnt; ++i)
        if (!graph->visited[i])
            dfs(graph, i, stack);
}