
#ifndef NSU_LEARNING_AVLTREE_H
#define NSU_LEARNING_AVLTREE_H
#define TREE struct tree
#include <stdio.h>
#include <malloc.h>

TREE {
    int value;
    int height;

    TREE *left, *right;
};


TREE* create(int value, int height) {
    TREE *res;
    res = (TREE*)malloc(sizeof(TREE));
    res -> value = value;
    res -> height = height;
    res -> left = NULL;
    res -> right = NULL;

    return res;
}

void add(TREE *tree, int value){
    TREE *child;
    if(tree != NULL){
        if(tree->left == NULL)
            child = create(value,tree->height + 1);
        else if(tree->right == NULL)
            child = create(value,tree->height + 1);
    }   else{
        add(tree->left,value);
        add(tree->right,value);
    }
}


#endif //NSU_LEARNING_AVLTREE_H
