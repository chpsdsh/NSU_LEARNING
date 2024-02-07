
#ifndef NSU_LEARNING_AVLTREE_H
#define NSU_LEARNING_AVLTREE_H
#define TREE struct tree
#include <stdio.h>
#include <malloc.h>

int max(int h1, int h2){
    if (h1>=h2)
        return h1;
    else
        return h2;
}
TREE {
    int key;
    int value;
    int height;

    TREE *left, *right;
};


TREE* create(int key, int value, int height) {
    TREE *res;
    res = (TREE*)malloc(sizeof(TREE));
    res -> key = key;
    res -> value = value;
    res -> height = 0;
    res -> left = NULL;
    res -> right = NULL;

    return res;
}

void add(TREE *tree,int key, int value){
    TREE *child;
    if(tree != NULL){
        if(tree->key > key){
            if(tree->left == NULL)
                tree->left = create(key,value,0);
            else
                add(tree->left,key,value);
        }
        else if (tree->key <= key){
            if(tree->right == NULL)
                tree->right = create(key,value,0);
            else
                add(tree->right,key,value);
        }

    }
}

void getHeight(TREE *tree){
   tree->height = max(tree->left->height,tree->right->height) + 1;
}

#endif //NSU_LEARNING_AVLTREE_H
