#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

typedef struct node {
    wchar_t symbol;
    int freq;
    struct node *left;
    struct pqueue *right;
} NODE;

typedef struct pqueue {
    int size;
    struct node **heap;
} PRIORITY_QUEUE;

PRIORITY_QUEUE *createQ() {
    PRIORITY_QUEUE *queue;
    queue = malloc(sizeof(PRIORITY_QUEUE));
    queue->size = 0;
    queue->heap = NULL;
}

NODE* createN(wchar_t symbol, int freq) {
    NODE *node = malloc(sizeof(NODE));
    node->symbol = symbol;
    node->freq = freq;
    return node;
}

int main() {
    setlocale(LC_ALL, "");

    FILE *input = fopen("in.txt", "rb");
    FILE *output = fopen("out.txt", "wb");
    wchar_t symbol;
    PRIORITY_QUEUE *queue = NULL;
    while (fread(&symbol, sizeof(wchar_t), 1, input) == 1) {

    }

    fclose(input);
    fclose(output);

    return 0;
}
