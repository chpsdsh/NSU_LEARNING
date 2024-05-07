#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define BYTE_SIZE 8
#define TWO_BYTE_SIZE 16

typedef struct huffmanCode {
    wchar_t symbol;
    unsigned long long code;
    int length;
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
    if (!stream) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
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
        writeBit(bit, stream);
    }
}

ERRORS readBit(int *bit, BITSTREAM *stream) {
    if (stream->pos == 0) {
        if (fread(&stream->data, sizeof(char), 1, stream->file) != 1)
            return readingError;
        stream->pos = BYTE_SIZE;
    }
    stream->pos -= 1;
    *bit = (stream->data >> stream->pos) & 1;
    return noError;
}

ERRORS readSymbol(wchar_t *symbol, BITSTREAM *stream) {
    *symbol = 0;
    for (int i = 0; i < TWO_BYTE_SIZE; i++) {
        *symbol = *symbol << 1;
        int bit;
        if (readBit(&bit, stream) == readingError)
            return readingError;
        *symbol = *symbol | bit;
    }
    return noError;
}

void clearBitstream(BITSTREAM *stream) {
    stream->data = stream->data << (BYTE_SIZE - stream->pos);
    fwrite(&(stream->data), sizeof(char), 1, stream->file);
}

PRIORITY_QUEUE *createQ() {
    PRIORITY_QUEUE *queue = malloc(sizeof(PRIORITY_QUEUE));
    if (!queue) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    queue->size = 0;
    queue->heap = NULL;
    return queue;
}

NODE *createN(wchar_t symbol, int freq, NODE *left, NODE *right) {
    NODE *node = malloc(sizeof(NODE));
    if (!node) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void resize(PRIORITY_QUEUE *queue, int size) {
    queue->heap = realloc(queue->heap, size * sizeof(NODE *));
    if (!queue->heap && size > 0) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
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
    fseek(input, 0, SEEK_END);
    long numBytes = ftell(input);
    rewind(input);

    for (int i = 0; i < (numBytes / sizeof(wchar_t)); i++) {
        symbol = fgetwc(input);
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

void GetCodes(NODE *root,  unsigned long long code, int length, HUFFMANCODE *codes, int *index) {
    if (lastLeave(root)) {
        codes[*index].symbol = root->symbol;
        codes[*index].length = length;
        codes[*index].code = code;
        (*index)++;
        return;
    }
    GetCodes(root->left, code << 1, length + 1, codes, index);
    GetCodes(root->right, (code << 1) | 1, length + 1, codes, index);
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


void destroy_tree(NODE *root) {
    if (root == NULL) {
        return;
    }

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
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

void encode(FILE *input, FILE *output) {
    PRIORITY_QUEUE *queue = initQueue(input);
    BITSTREAM *stream = createBitStream(output);
    HUFFMANCODE *codes = malloc(queue->size * sizeof(HUFFMANCODE));
    NODE *root = createTree(queue);
    fwrite(&(root->freq), sizeof(int), 1, stream->file);
    treeToFile(root, stream);
    int index = 0;
    GetCodes(root, 0, 0, codes, &index);

    fseek(input, 0, SEEK_END);
    long numBytes = ftell(input);
    rewind(input);
    wchar_t symbol;
    for (int i = 0; i < (numBytes / sizeof(wchar_t)); i++) {
        symbol = fgetwc(input);
        codeInput(symbol, codes, stream, index);
    }
    clearBitstream(stream);
    free(codes);
    free(queue->heap);
    free(queue);
    free(stream);
    destroy_tree(root);
}


NODE *getTree(BITSTREAM *stream) {
    int bit;
    if (readBit(&bit, stream) == readingError)
        return NULL;
    if (bit == 1) {
        wchar_t symbol;
        if (readSymbol(&symbol, stream) == readingError)
            return NULL;
        return createN(symbol, 0, NULL, NULL);
    }
    NODE *left = getTree(stream);
    NODE *right = getTree(stream);
    return createN(0, 0, left, right);
}

ERRORS unzip(NODE *root, BITSTREAM *stream, wchar_t *symbol) {
    NODE *current = root;
    while (!lastLeave(current)) {
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
    int length;
    fread(&length, sizeof(int), 1, stream->file);
    NODE *root = getTree(stream);

    for (int i = 0; i < length; i++) {
        wchar_t symbol;
        if (unzip(root, stream, &symbol) == readingError) {
            fclose(stream->file);
            free(stream);
            return;
        }
        fwrite(&symbol, sizeof(wchar_t), 1, output);
    }
    destroy_tree(root);
    free(stream);

}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    char *action = argv[1];
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];

    if (strcmp(action, "c") == 0) {
        FILE *input = fopen(inputFileName, "rb");
        FILE *output = fopen(outputFileName, "wb");
        encode(input, output);
        fclose(input);
        fclose(output);
    } else if (strcmp(action, "d") == 0) {
        FILE *input = fopen(inputFileName, "rb");
        FILE *output = fopen(outputFileName, "wb");
        decode(input, output);
        fclose(input);
        fclose(output);
    }

    return 0;
}
