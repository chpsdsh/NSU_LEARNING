#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define BYTE_SIZE 8
#define TWO_BYTE_SIZE 16

typedef struct huffmanCode {
    wchar_t symbol;
    unsigned long long code;
    unsigned int length;
} HUFFMANCODE;

typedef struct BitStream {
    FILE *file;
    wchar_t data;
    int pos;
} BITSTREAM;

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
    if (stream->pos == BYTE_SIZE) {
        fwrite(&(stream->data), sizeof(char), 1, stream->file);
        stream->pos = 0;
        stream->data = 0;
    }
    stream->data = bit | (stream->data << 1);
    stream->pos++;
}

void writeSymbol(wchar_t symbol, BITSTREAM *stream) {
    for (int i = TWO_BYTE_SIZE - 1; i >= 0; i--) {
        int bit = (symbol >> i) & 1;
        printf("%d", bit);
        writeBit(bit, stream);
    }

}

ERRORS readBit(int *bit, BITSTREAM *stream) {
    if (stream->pos == 0) {
        if (fread(&(stream->data), sizeof(char), 1, stream->file) != 1)
            return readingError;
        stream->pos = BYTE_SIZE;
    }
    stream->pos -= 1;
    *bit = (stream->data >> stream->pos) & 1;
    return noError;
}

ERRORS readSymbol(wchar_t *symbol, BITSTREAM *stream) {
    *symbol = 0;
    for (int i = 0; i < TWO_BYTE_SIZE - 1; i++) {
        wint_t wchar;
        if ((wchar = fgetwc(stream->file)) == WEOF)
            return readingError;
        *symbol = *symbol << 1;
        *symbol = *symbol | (wchar & 1);
    }
    return noError;
}

void clearBitstream(BITSTREAM *stream) {
    stream->data = stream->data << (BYTE_SIZE - stream->pos);
    fwrite(&(stream->data), sizeof(char), 1, stream->file);
}

PRIORITY_QUEUE *createQ() {
    PRIORITY_QUEUE *queue = malloc(sizeof(PRIORITY_QUEUE));
    queue->size = 0;
    queue->heap = NULL;
    return queue;
}

NODE *createN(wchar_t symbol, int freq, NODE *left, NODE *right) {
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
    queue->size = size;

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

    wchar_t symbol;
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

    puts("");
    printf("%d", queue->size);
    for (int i = 0; i < queue->size; i++) {
        printf("%c %d\n", queue->heap[i]->symbol, queue->heap[i]->freq);
    }
    puts("______");
    rewind(input);
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

void GetCocks(NODE *root, unsigned long long int code, unsigned int length, HUFFMANCODE *codes, int *index) {
    if (lastLeave(root)) {
        codes[*index].symbol = root->symbol;
        codes[*index].length = length;
        codes[*index].code = code;
        (*index)++;
        return;
    }
    GetCocks(root->left, code << 1, length + 1, codes, index);
    GetCocks(root->right, (code << 1) | 1, length + 1, codes, index);
}

void CodeQueue(PRIORITY_QUEUE *queue, BITSTREAM *stream) {
    for (int i = 0; i < queue->size; i++) {
        fwrite(&(queue->heap[i]->symbol), sizeof(wchar_t), 1, stream->file);
        fwrite(&(queue->heap[i]->freq), sizeof(int), 1, stream->file);
    }
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
        printf("%d", bit);
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

    PRIORITY_QUEUE *queue = initQueue(input);

    BITSTREAM *stream = createBitStream(output);
    fwrite(&(queue->size), sizeof(int), 1, stream->file);
    printf("%d\n", queue->size);
    CodeQueue(queue, stream);
    HUFFMANCODE *codes = malloc(queue->size * sizeof(HUFFMANCODE));
    NODE *root = createTree(queue);
    fwrite(&(root->freq), sizeof(int), 1, stream->file);

    print_tree(root);
    int index = 0;
    GetCocks(root, 0, 0, codes, &index);

    wchar_t symbol;

    while ((symbol = fgetwc(input)) != WEOF) {

        codeInput(symbol, codes, stream, index);
    }
    clearBitstream(stream);
    free(queue);
    free(codes);
    free(stream);
}


PRIORITY_QUEUE *DecodeQueue(BITSTREAM *stream, int size) {
    PRIORITY_QUEUE *queue = createQ();
    resize(queue, size);
    for (int i = 0; i < size; i++) {
        wchar_t symbol;
        int freq;
        fread(&symbol, sizeof(wchar_t), 1, stream->file);
        fread(&freq, sizeof(int), 1, stream->file);
        NODE *node = createN(symbol, freq, NULL, NULL);
        queue->heap[i] = node;
    }
    return queue;
}

ERRORS unzip(NODE *root, BITSTREAM *stream, wchar_t *symbol) {
    NODE *current = root;
    while (current->left != NULL) {
        int bit;
        if (readBit(&bit, stream) == readingError)
            return readingError;
        if (bit == 0)
            current = current->left;
        else
            current = current->right;
    }
    *symbol = current->symbol;
    return noError;
}

void decode(FILE *input, FILE *output) {
    BITSTREAM *stream = createBitStream(input);
    int size;
    fread(&size, sizeof(int), 1, stream->file);
    PRIORITY_QUEUE *queue = DecodeQueue(stream, size);
    NODE *root = createTree(queue);
    print_tree(root);
    int length;
    fread(&length, sizeof(int), 1, stream->file);
    for (int i = 0; i < length; i++) {
        wchar_t symbol;
        if (unzip(root, stream, &symbol) == readingError)
            return;
        fprintf(output, "%lc", symbol);
    }
}


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    char *action = argv[1];
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];


    if (strcmp(action, "c") == 0) {
        FILE *input = fopen(inputFileName, "r+, ccs=UTF-8");
        FILE *output = fopen(outputFileName, "wb");
        encode(input, output);
        fclose(input);
        fclose(output);
    } else if (strcmp(action, "d") == 0) {
        FILE *input = fopen(inputFileName, "rt+");
        FILE *output = fopen(outputFileName, "w");
        decode(input, output);
        fclose(input);
        fclose(output);
    }

    return 0;
}
