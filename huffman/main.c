#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 8
#define MAX_OCT_SIZE 32


typedef struct huffmanCode {
    uint32_t symbol;
    uint32_t code;
    int length;
} HUFFMANCODE;

typedef struct BitStream {
    FILE *file;
    uint32_t data;
    int pos;
} BITSTREAM;

typedef struct node {
    uint32_t symbol;
    int freq;
    struct node *left;
    struct node *right;
} NODE;

typedef struct pqueue {
    int size;
    struct node **heap;
} PRIORITY_QUEUE;

typedef enum error {
    noError,
    readingError,
} ERRORS;

BITSTREAM *createBitStream(FILE *file) {
    BITSTREAM *stream = malloc(sizeof(BITSTREAM));
    stream->file = file;
    stream->data = 0;
    stream->pos = 0;
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

void writeSymbol(uint32_t symbol, BITSTREAM *stream) {
    for (int i = MAX_OCT_SIZE - 1; i >= 0; i--) {
        int bit = (symbol >> i) & 1;
        //printf("%d",bit);
        writeBit(bit, stream);
    }
    //puts("");
}

ERRORS readBit(int *bit, BITSTREAM *stream) {
    if (stream->pos == 0) {
        if (fread(&(stream->data), sizeof(char), 1, stream->file) != 1)
            return readingError;
        stream->pos = BUF_SIZE;
    }
    stream->pos -= 1;
    *bit = (stream->data >> stream->pos) & 1;
    //printf("%d",*bit);
    return noError;
}

ERRORS readSymbol(uint32_t *symbol, BITSTREAM *stream) {
    *symbol = 0;
    for (int i = 0; i < MAX_OCT_SIZE; i++) {
        *symbol = *symbol << 1;
        int bit;
        if (readBit(&bit, stream) == readingError)
            return readingError;
        *symbol = *symbol | bit;
    }

    return noError;
}

void clearBitstream(BITSTREAM *stream) {
    stream->data = stream->data << (BUF_SIZE - stream->pos);
    fwrite(&(stream->data), sizeof(char), 1, stream->file);
}

PRIORITY_QUEUE *createQ() {
    PRIORITY_QUEUE *queue = malloc(sizeof(PRIORITY_QUEUE));
    queue->size = 0;
    queue->heap = NULL;

    return queue;
}

NODE *createN(uint32_t symbol, int freq, NODE *left, NODE *right) {
    NODE *node = malloc(sizeof(NODE));
    if (node != NULL) {
        node->symbol = symbol;
        node->freq = freq;
        node->left = left;
        node->right = right;
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
    resize(queue, queue->size + 1);
    int index = queue->size - 1;

    while (index > 0 && node->freq >= queue->heap[index - 1]->freq) {
        queue->heap[index] = queue->heap[index - 1];
        index--;
    }
    queue->heap[index] = node;
}

PRIORITY_QUEUE *initQueue(FILE *input) {
    if (input == NULL) {
        return NULL;
    }

    uint32_t symbol;
    PRIORITY_QUEUE *queue = createQ();


    while ((symbol = fgetwc(input)) != WEOF) {
        printf("%lc", symbol);
        int inQueue = 0;
        for (int i = 0; i < queue->size; i++) {
            if (queue->heap[i]->symbol == symbol) {
                queue->heap[i]->freq++;
                while (i > 0 && queue->heap[i]->freq >= queue->heap[i - 1]->freq) {
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
            enqueue(queue, createN(symbol, 1, NULL, NULL));
        }
    }
    puts("_____");
    for (int i = 0; i < queue->size; i++) {
        printf("%c %d\n", queue->heap[i]->symbol, queue->heap[i]->freq);
    }
    puts("______");
    return queue;
}

NODE *createTree(PRIORITY_QUEUE *queue) {
    while (queue->size > 1) {
        NODE *left = queue->heap[--queue->size];
        NODE *right = queue->heap[--queue->size];
        NODE *node = createN(0, left->freq + right->freq, left, right);
        enqueue(queue, node);
    }
    return queue->heap[0];
}

int lastLeave(NODE *root) {
    return !root->left;
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
        //printf("1");
        //printf("%c", root->symbol);
        writeSymbol(root->symbol, stream);
        return;
    }
    writeBit(0, stream);
    //printf("0");
    treeToFile(root->left, stream);
    treeToFile(root->right, stream);
}

void codeInput(uint32_t symbol, HUFFMANCODE *codes, BITSTREAM *stream, int codesLen) {
    int i;
    for (i = 0; i < codesLen; i++) {
        if (codes[i].symbol == symbol) {
            break;
        }
    }
    for (int j = codes[i].length - 1; j >= 0; j--) {
        int bit = (codes[i].code >> j) & 1;
        //printf("%d",bit);
        writeBit(bit, stream);
    }
}

void print_tree(NODE *tree) {
    printf("%d %lc -- %d\n", tree->symbol, tree->symbol, tree->freq);
    if (tree->left != NULL)
        print_tree(tree->left);
    if (tree->right != NULL)
        print_tree(tree->right);
    return;
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
    print_tree(root);
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
    uint32_t symbol;
    while ((symbol = fgetwc(input)) != WEOF) {

        codeInput(symbol, codes, stream, index);
    }
    clearBitstream(stream);
    free(queue);
    free(codes);
    free(stream);
    return;
}

NODE *getTree(BITSTREAM *stream) {
    int bit;
    if (readBit(&bit, stream) == readingError)
        return NULL;
    if (bit == 1) {
        int symbol;
        //puts("1");
        if (readSymbol(&symbol, stream) == readingError)
            return NULL;
        //printf("%lc\n", symbol);
        return createN(symbol, 0, NULL, NULL);
    }
    NODE *left = getTree(stream);
    NODE *right = getTree(stream);
    return createN(0, 0, left, right);
}

ERRORS GetSymbol(uint32_t *symbol, NODE *root, BITSTREAM *stream) {
    NODE *current = root;
    while (!lastLeave(current)) {
        //printf("%c", current->symbol);
        int bit;
        if (readBit(&bit, stream) == readingError)
            return readingError;
        //printf("%d", bit);
        if (bit == 0)
            current = current->left;
        else
            current = current->right;
    }
    *symbol = current->symbol;
    printf("%lc ",*symbol);
    return noError;
}

void decode(FILE *input, FILE *output) {

    BITSTREAM *stream = createBitStream(input);
    int length;
    fread(&length, sizeof(int), 1, input);
    printf("%d\n", length);
    NODE *root = getTree(stream);
    //puts("");
    print_tree(root);
    for (int i = 0; i < length; i++) {
        //puts("penis");
        uint32_t symbol;
        if (GetSymbol(&symbol, root, stream) == readingError) {

            return;
        }
        //printf("%d ", symbol);
        if (symbol <= 0x8F)
            fwrite(&symbol, sizeof(char), 1, output);
        else if (0x8F < symbol && symbol <= 0x8FF)
            fwrite(&symbol, 2 * sizeof(char), 1, output);
        else if (0x8FF < symbol && symbol <= 0x8FFF)
            fwrite(&symbol, 3 * sizeof(char), 1, output);
        else
            fwrite(&symbol, 4 * sizeof(char), 1, output);
    }
    free(stream);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    char *action = argv[1];
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];

    FILE *input = fopen(inputFileName, "r+");
    FILE *output = fopen(outputFileName, "w+");

    if (strcmp(action, "c") == 0)
        encode(input, output);
    else if (strcmp(action, "d") == 0)
        decode(input, output);

    fclose(input);
    fclose(output);

    return 0;
}
