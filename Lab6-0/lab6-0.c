#include <stdio.h>
#include <malloc.h>
#include "avltree.h"
int main() {
    FILE *file = fopen("in.txt", "r");
    int N;
    fscanf(file, "%d", &N);
    if(N==0){
        puts("0");
        return 0;
    }
    TREE*root = NULL;
    TREE *nodearr = (TREE*)malloc(N*sizeof (TREE));
    for(int i = 0; i < N; i++){
        create(0,nodearr, i);
        int value;
        fscanf(file, "%d", &value);
        root = insert(root,value, &nodearr[i]);
    }
    printf("%d", root->height+1);
    fclose(file);
    free(nodearr);
}