#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "avltree.h"

int main(){
    int N;
    scanf_s("%d",&N);
    if(N==0){
        puts("0");
        return 0;
    }

    int value;
    scanf_s("%d",&value);
    TREE *tree = create(0,value);

    for (int i = 1; i < N; i++){
        scanf_s("%d",&value);
        insert(tree,i,value);;
        printf("%d\n",tree->height);
    }
    printf("%d", tree->height+1);
}