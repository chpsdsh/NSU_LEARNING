#include "avltree.h"
#include <malloc.h>
#include <stdio.h>


int main() {
    FILE *file = fopen("in.txt", "r");

    int N;
    if(!fscanf(file, "%d", &N)){
        fclose(file);
        return 0;
    }


    if(N==0){
        puts("0");
        return 0;
    }

    TREE *root = NULL;
    TREE *nodearr = (TREE*)malloc(N*sizeof(TREE));

    for(int i = 0; i < N; i++){
        int value;
        if(!fscanf(file, "%d", &value)){
            fclose(file);
            return 0;
        }
        create(value,nodearr, i);
        root = insert(root,value, &nodearr[i]);
    }

    printf("%d\n", getHeight(root)+1);
    InOrder(root);
    int value;
    if(!fscanf(file, "%d", &value)){
        fclose(file);
        return 0;
    }

    Search(root,value);
    fclose(file);
    free(nodearr);
}