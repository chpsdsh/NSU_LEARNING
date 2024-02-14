#include "avltree.h"
#include <malloc.h>
#include <stdio.h>


int main() {
    FILE *file = fopen("in.txt", "r");

    int N;
    fscanf(file, "%d", &N);

    if(N==0){
        puts("0");
        return 0;
    }

    TREE *root = NULL;
    TREE *nodearr = (TREE*)malloc(N*sizeof(TREE));

    for(int i = 0; i < N; i++){
        int value;
        fscanf(file, "%d", &value);
        create(value,nodearr, i);
        root = insert(root,value, &nodearr[i]);
    }

    printf("%d", root->height + 1);

    fclose(file);
    free(nodearr);
}