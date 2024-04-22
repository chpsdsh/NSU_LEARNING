#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

typedef struct node {
    unsigned long symbol;
    long int freq;
    struct node *left;
    struct node *right;
} NODE;

typedef struct pqueue {
    int size;
    struct node **heap;
} PRIORITY_QUEUE;

typedef struct huffmanCode {
    int len;
    int code;
} HUFFMANCODE;

typedef struct BitStream {
    FILE *file;
    unsigned long data;
    int pos;
} BITSTREAM;


BITSTREAM *createBitStream(FILE *file) {
    BITSTREAM *stream = malloc(sizeof(BITSTREAM));
    stream->file = file;
    stream->data = 0;
    stream->pos = 0;
}


PRIORITY_QUEUE *createQ() {
    PRIORITY_QUEUE *queue = malloc(sizeof(PRIORITY_QUEUE));
    queue->size = 0;
    queue->heap = NULL;
    return queue;
}

NODE *createN(wchar_t symbol, int freq) {
    NODE *node = malloc(sizeof(NODE));
    node->symbol = symbol;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void resize(PRIORITY_QUEUE *queue, int size) {
    queue->heap = realloc(queue->heap, size * sizeof(NODE *));
    queue->size = size;
}

void enqueue(PRIORITY_QUEUE *queue, NODE *node) {
    resize(queue, queue->size + 1);
    int index = queue->size - 1;
    queue->heap[index] = node;
    while (index > 0 && queue->heap[index]->freq >= queue->heap[index - 1]->freq) {
        NODE *temp = queue->heap[index];
        queue->heap[index] = queue->heap[index - 1];
        queue->heap[index - 1] = temp;
        index--;
    }

}

PRIORITY_QUEUE *initQueue(FILE *input, FILE *output) {
    wint_t symbol;
    PRIORITY_QUEUE *queue = createQ();
    while ((symbol = fgetwc(input)) != WEOF) {
        int inQueue = 0;
        for (int i = 0; i < queue->size; i++) {
            if (queue->heap[i]->symbol == symbol) {
                queue->heap[i]->freq++;
                while (i > 0 && queue->heap[i]->freq > queue->heap[i - 1]->freq) {
                    NODE *temp = queue->heap[i];
                    queue->heap[i] = queue->heap[i - 1];
                    queue->heap[i - 1] = temp;
                    i--;
                }
                inQueue = 1;
                break;
            }
        }
        if (!inQueue) {
            enqueue(queue, createN(symbol, 1));
        }
    }


    for (int i = 0; i < queue->size; i++) {
        fwprintf(output, L"%d %lc\n", queue->heap[i]->freq, queue->heap[i]->symbol);

    }
    return queue;
}

void sortQueue(PRIORITY_QUEUE *queue, int index) {
    while (index > 0 && queue->heap[index]->freq > queue->heap[index - 1]->freq) {
        NODE *temp = queue->heap[index];
        queue->heap[index] = queue->heap[index - 1];
        queue->heap[index - 1] = temp;
        index--;
    }
}

NODE *createTree(PRIORITY_QUEUE *queue) {
    int index = queue->size - 1;

    while (queue->size > 0) {
        NODE *node = createN(WEOF, queue->heap[index]->freq + queue->heap[index - 1]->freq);
        node->left = queue->heap[index];
        node->right = queue->heap[index - 1];
        resize(queue, queue->size - 1);
        queue->heap[queue->size - 1] = node;
        index--;
        sortQueue(queue, index);
    }
    return queue->heap[0];
}

int lastLeaf(NODE *root) {
    if (root->left == NULL)
        return 1;
    return 0;
}

void GetCocks(NODE *root, HUFFMANCODE *codes, unsigned int code, int len, int index) {
    if (lastLeaf(root)) {
        codes[index].len = len;
        codes[index++].code = code;
    }
    GetCocks(root->left, codes, code << 1, len + 1, index);
    GetCocks(root->right, codes, (code << 1) | 1, len + 1, index);
}

void encode(FILE *input, FILE *output) {
    PRIORITY_QUEUE *queue = initQueue(input, output);
    HUFFMANCODE *codes = malloc(queue->size * sizeof(HUFFMANCODE *));
    BITSTREAM *stream = createBitStream(output);


}

int main() {
    setlocale(LC_ALL, "");

    FILE *input = fopen("in.txt", "r, ccs=UTF-8");
    FILE *output = fopen("out.txt", "w, ccs=UTF-8");
    PRIORITY_QUEUE *queue = initQueue(input, output);
    fclose(input);
    fclose(output);

    return 0;
}
