
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


TREE* create(int key, int value) {
    TREE *res;
    res = (TREE*)malloc(sizeof(TREE));
    res -> key = key;
    res -> value = value;
    res -> height = 0;
    res -> left = NULL;
    res -> right = NULL;

    return res;
}
void updateHeight(TREE *tree);
void balance(TREE *tree);

void insert(TREE *tree,int key, int value){
    if(tree->key > key){
        if(tree->left == NULL)
            tree->left = create(key,value);
        else
            insert(tree->left,key,value);
    }
    else if (tree->key <= key){
        if(tree->right == NULL)
            tree->right = create(key,value);
        else
            insert(tree->right,key,value);
    }
    updateHeight(tree);
    balance(tree);


}

int getHeight(TREE*tree){
    if (tree == NULL)
        return -1;
    else
        return tree->height;
}

void updateHeight(TREE *tree){
    tree->height = max(getHeight(tree->left),getHeight(tree->right)) + 1;
}

int IsBalanced(TREE *tree){
    if(tree != NULL)
        return getHeight(tree->right) - getHeight(tree->left);
}

void swap(TREE *t1, TREE *t2){
    int t1_key = t1->key;
    t1->key = t2->key;
    t2->key = t1_key;
    int t1_value = t1->value;
    t1->value = t2->value;
    t2->value = t1_value;
}

void rightTurn(TREE *tree){
    swap(tree,tree->left);
    TREE *buf = tree->right;
    tree->right = tree->left;
    tree->left = tree->right->left;
    tree->right->left = tree->right->right;
    tree->right->right = buf;
    updateHeight(tree->right);
    updateHeight(tree);
}

void leftTurn(TREE *tree){
    swap(tree,tree->right);
    TREE *buf = tree->left;
    tree->left = tree->right;
    tree->right = tree->left->right;
    tree-> left->right = tree->left->left;
    tree->left->left = buf;
    updateHeight(tree->left);
    updateHeight(tree);
}

void balance(TREE *tree){
    int balance = IsBalanced(tree);
    if(balance == -2){
        if(IsBalanced(tree->left)==1)
            leftTurn(tree);
        rightTurn(tree);
    }
    else if(balance == 2){
        if(IsBalanced(tree->left)==-1)
            rightTurn(tree);
        leftTurn(tree);
    }
}

#endif //NSU_LEARNING_AVLTREE_H