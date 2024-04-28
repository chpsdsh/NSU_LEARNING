#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define BUF_SIZE 8
#define MAX_OCT_SIZE 32

typedef struct node {
    wchar_t symbol;
    int freq;
    struct node *left;
    struct node *right;
} NODE;

typedef struct pqueue {
    int size;
    struct node **heap;
} PRIORITY_QUEUE;

typedef struct huffmanCode {
    wchar_t symbol;
    long code;
    int length;
} HUFFMANCODE;

typedef struct BitStream {
    FILE *file;
    long data;
    int pos;
} BITSTREAM;

BITSTREAM *createBitStream(FILE *file) {
    BITSTREAM *stream = malloc(sizeof(BITSTREAM));
    if (stream != NULL) {
        stream->file = file;
        stream->data = 0;
        stream->pos = 0;
    }
    return stream;
}

void writeBit(int bit, BITSTREAM *stream) {
    if (stream->pos == BUF_SIZE) {
        fwrite(&(stream->data), sizeof(char), 1, stream->file);
        stream->pos = 0;
        stream->data = 0;
    }
    stream->data = bit | (stream->data << 1);
    stream->pos++;
}

void writeSymbol(wchar_t symbol, BITSTREAM *stream) {
    for (int i = MAX_OCT_SIZE - 1; i >= 0; i--) {
        int bit = (symbol >> i) & 1;
        writeBit(bit, stream);
    }
}

void clearBitstream(BITSTREAM *stream) {
    stream->data = stream->data << (BUF_SIZE - stream->pos);
    fwrite(&(stream->data), sizeof(char), 1, stream->file);
}

PRIORITY_QUEUE *createQ() {
    PRIORITY_QUEUE *queue = malloc(sizeof(PRIORITY_QUEUE));
    if (queue != NULL) {
        queue->size = 0;
        queue->heap = NULL;
    }
    return queue;
}

NODE *createN(wchar_t symbol, int freq) {
    NODE *node = malloc(sizeof(NODE));
    if (node != NULL) {
        node->symbol = symbol;
        node->freq = freq;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void resize(PRIORITY_QUEUE *queue, int size) {
    queue->heap = realloc(queue->heap, size * sizeof(NODE *));
    if (queue->heap != NULL) {
        queue->size = size;
    }
}

void enqueue(PRIORITY_QUEUE *queue, NODE *node) {
    if (queue->heap == NULL) {
        queue->size = 0;
    }
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

PRIORITY_QUEUE *initQueue(FILE *input) {
    if (input == NULL) {
        return NULL;
    }
    wint_t symbol;
    PRIORITY_QUEUE *queue = createQ();
    if (queue == NULL) {
        return NULL;
    }
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

int lastLeave(NODE *root) {
    return !root->left;
}

NODE *createTree(PRIORITY_QUEUE *queue) {
    int index = queue->size - 1;
    while (index > 0) {
        NODE *node = createN(WEOF, queue->heap[index]->freq + queue->heap[index - 1]->freq);
        if (node == NULL) {
            return NULL;
        }
        node->left = queue->heap[index - 1];
        node->right = queue->heap[index];
        queue->heap[--index] = node;
        resize(queue, queue->size - 1);
        sortQueue(queue, index);
    }
    return queue->heap[0];
}

void GetCocks(NODE *root, unsigned int code, int length, HUFFMANCODE *codes, int *index) {
    if (root->left == NULL) {
        codes[*index].symbol = root->symbol;
        codes[*index].length = length;
        codes[*index].code = code;
        (*index)++;
        return;
    }
    GetCocks(root->left, code << 1, length + 1, codes, index);
    GetCocks(root->right, (code << 1) | 1, length + 1, codes, index);
}

void treeToFile(NODE *root, BITSTREAM *stream) {
    if (lastLeave(root)) {
        writeBit(1, stream);
        writeSymbol(root->symbol, stream);
        return;
    }
    writeBit(0, stream);
    treeToFile(root->left, stream);
    treeToFile(root->right, stream);
}

void codeInput(wchar_t symbol, HUFFMANCODE *codes, BITSTREAM *stream, int codesLen) {
    int i;
    for (i = 0; i < codesLen; i++) {
        if (codes[i].symbol == symbol) {
            break;
        }
    }
    for (int j = codes[i].length - 1; j >= 0; j--) {
        int bit = (codes[i].code >> j) & 1;
        writeBit(bit, stream);
    }
}

void encode(FILE *input, FILE *output) {
    if (input == NULL || output == NULL) {
        return;
    }
    PRIORITY_QUEUE *queue = initQueue(input);
    if (queue == NULL) {
        return;
    }
    BITSTREAM *stream = createBitStream(output);
    if (stream == NULL) {
        free(queue);
        return;
    }
    HUFFMANCODE *codes = malloc(queue->size * sizeof(HUFFMANCODE));
    if (codes == NULL) {
        free(queue);
        free(stream);
        return;
    }
    NODE *root = createTree(queue);
    if (root == NULL) {
        free(queue);
        free(stream);
        free(codes);
        return;
    }
    int index = 0;
    GetCocks(root, 0, 0, codes, &index);
    fwrite(&(root->freq), sizeof(int), 1, stream->file);
    treeToFile(root, stream);
    rewind(input);
    wint_t symbol;
    while ((symbol = fgetwc(input)) != WEOF) {
        codeInput(symbol, codes, stream, index);
    }
    clearBitstream(stream);
    free(queue);
    free(codes);
    free(stream);
}

int main() {
    setlocale(LC_ALL, "");
    FILE *input = fopen("in.txt", "r, ccs=UTF-8");
    FILE *output = fopen("out.txt", "w+");
    if (input != NULL && output != NULL) {
        encode(input, output);
        fclose(input);
        fclose(output);
    }
    return 0;
}
