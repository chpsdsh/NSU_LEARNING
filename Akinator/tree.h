#ifndef TREEKINATOR_TREE_H
#define TREEKINATOR_TREE_H
#define TREE struct tree
#include <stdio.h>
#include <malloc.h>

TREE {
        char* value;
        int nmb;
        TREE *left, *right;
};


TREE* create(char* value,int number) {
    TREE *res;
    res = (TREE*)malloc(sizeof(TREE));

    res -> value = value;
    res -> nmb = number;
    res -> left = NULL;
    res -> right = NULL;

    return res;
}

void add(TREE *T, char *value, int nmb){//adding
    TREE *child;
    if(T != NULL)
    {
        if(T->nmb * 2 == nmb) {
            child = create(value,nmb);
            T->left = child;
        }
        else if(T->nmb * 2 + 1 == nmb) {
            child = create(value,nmb);
            T->right = child;
        }
        else{
            add(T->left,value,nmb);
            add(T->right,value,nmb);
        }
    }
}

#endif //TREEKINATOR_TREE_H
