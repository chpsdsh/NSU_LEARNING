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
    unsigned int symbol;
    unsigned int code;
} HUFFMANCODE;

typedef struct BitStream {
    FILE *file;
    unsigned long data;
    int pos;
} BITSTREAM;

/*void InOrder(NODE *T) {
    if (T->left != NULL)
        InOrder(T->left);

    printf("%lc\n", T->symbol);

    if (T->right != NULL)
        InOrder(T->right);
}
*/

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

NODE *delete(PRIORITY_QUEUE *queue) {
    NODE *node = queue->heap[queue->size - 1];
    queue->heap = realloc(queue->heap, (--queue->size) * sizeof(NODE *));
    return node;
}

PRIORITY_QUEUE *initQueue(FILE *input) {
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
    /*for (int i = 0; i < queue->size; i++)
        printf("%lc %d\n", queue->heap[i]->symbol, queue->heap[i]->freq);
        */
    return queue;
}


int emptyQ(PRIORITY_QUEUE *queue) {
    if (queue->size == 0)
        return 1;
    return 0;
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
    //NODE *min = delete(queue);
    //PRIORITY_QUEUE *NewQueue = createQ();
    int index = queue->size - 1;
    while (index > 0) {
        //printf("%d %d %d\n", index,queue->heap[index]->freq,queue->heap[index - 1]->freq);

        NODE *node = createN(WEOF, queue->heap[index]->freq + queue->heap[index - 1]->freq);
        node->left = queue->heap[index - 1];
        node->right = queue->heap[index];
        queue->heap[--index] = node;
        printf("%d\t", queue->heap[index]->freq);
        resize(queue, queue->size - 1);
        //index--;
        //printf("%d\n", index);
        sortQueue(queue, index);
        printf("%d\n", queue->heap[index]->freq);

    }
    //puts("penis");
    //InOrder(queue->heap[0]);
    return queue->heap[0];
}


void GetCocks(NODE *root, unsigned int code, FILE *output) {
    //printf("%lc %d \n" , root->symbol, code);
    if (root->left == NULL) {
        printf("%lc %d\t", root->symbol, code);
        fprintf(output, "%d_%d\t", root->symbol, code);
        /*codes[index].symbol = root->symbol;
        codes[index].code = code;
        index++;*/
        return;
    }
    GetCocks(root->left, code << 1, output);
    GetCocks(root->right, (code << 1) | 1, output);

}

/*void treeToFile(HUFFMANCODE *codes, int size) {
    FILE *output = fopen("out.txt", "w, ccs=UTF-8");
    for (int i = 0; i < size; i++)
        fprintf(output, "%d %d ", codes[i].symbol, codes[i].code);
    fclose(output);
}
*/
void GetCocksTable(NODE *root, int size) {
    //HUFFMANCODE *codes = malloc(size * sizeof(HUFFMANCODE*));
    //if (!codes)
    //  return;
    FILE *output = fopen("out.txt", "w+");
    GetCocks(root, 0, output);
    /*for (int i = 0; i< size-1;i++){
        printf("%d\t",codes[i]);
    }*/
    //treeToFile(codes, size);
    fclose(output);
}


void encode(FILE *input) {
    PRIORITY_QUEUE *queue = initQueue(input);
    //BITSTREAM *stream = createBitStream(output);
    NODE *root = createTree(queue);
    GetCocksTable(root, queue->size);
}

int main() {
    setlocale(LC_ALL, "");

    FILE *input = fopen("in.txt", "r, ccs=UTF-8");
    encode(input);
    fclose(input);

    return 0;
}
