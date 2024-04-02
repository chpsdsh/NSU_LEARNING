#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct stack{
    int value;
    struct stack *next;
}STACK;

STACK* createS() {
    STACK *Telem = (STACK*)malloc(sizeof(STACK));
    Telem->next = NULL;
    return Telem;
}

void push(STACK *S, int value) {
    STACK *elem = (STACK*)malloc(sizeof(STACK));
    elem->value = value;
    elem->next = S->next;
    S->next = elem;
}

int empty(STACK *S) {
    return S->next == NULL;
}

int pop(STACK *S) {
    if (empty(S))
        return -1;
    STACK *first = S->next;
    int val = first->value;
    S->next = first->next;
    free(first);
    return val;
}

void print(STACK *S){//prints stack
    STACK *ptr = S-> next;
    while (ptr != NULL){
        printf("%d ",ptr->value);
        ptr = ptr->next;
    }
}

void dfs1(GRAPH* graph, int index,  STACK *stack) {
    graph->visited[index] = 1;
    for (int i = 0; i < graph->nodeCnt; ++i)
        if (graph->matrix[index * graph->nodeCnt + i] && !graph->visited[i])
            dfs1(graph, i, stack);
    push(stack, index);
}

void dfs2(GRAPH* graph, int node, int colour) {
    graph->visited[node] = colour;
    for (int i = 0; i < graph->nodeCnt; ++i) {
        if (graph->revmatrix[node * graph->nodeCnt + i] && !graph->visited[i]) {
            dfs2(graph, i, colour);
        }
    }
}

int max(int *array, int length){
    int max = -9999;
    for(int i = 0; i < length; i++)
        max = max < array[i] ? array[i] : max;
    return max;
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
}

void kosaraju(GRAPH *graph){
    int node;
    int colour = 0;
    STACK *stack = createS();

    for(int i = 0; i < graph->nodeCnt; i++)
        if (!graph->visited[i])
            dfs1(graph, i, stack);

    for(int i = 0; i < graph->nodeCnt; i++)
        graph->visited[i] = 0;

    while(!empty(stack)){
        node = pop(stack);
        if(!graph->visited[node]){

            dfs2(graph, node, ++colour);
        }
    }

    printResults(graph);

    free(stack);
}

int main(){
    GRAPH *graph = fill_graph();
    kosaraju(graph);
    return 0;
}
