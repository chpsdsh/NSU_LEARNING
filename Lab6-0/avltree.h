#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H
#define TREE struct tree
#include <stdio.h>
#include <malloc.h>

int max(int h1, int h2){
    if (h1>=h2)
        return h1;
    else
        return h2;
}

TREE{
    int value;
    int height;
    TREE *left;
    TREE *right;
};

TREE*create(int value, TREE*arr, int counter){
    arr[counter].height = 0;
    arr[counter].value = value;
    arr[counter].left = arr[counter].right = 0;
    return &arr[counter];
}

int getHeight(TREE*tree){
    if (tree == NULL)
        return -1;
    else
        return tree->height;
}

int updateHeight(TREE *tree){
    tree->height = max(getHeight(tree->left),getHeight(tree->right)) + 1;
    return tree->height;
}


TREE *rightTurn(TREE*tree){
    TREE*left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = updateHeight(tree);
    left->height = updateHeight(left);
    return left;
}

TREE *leftTurn(TREE*tree){
    TREE*right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = updateHeight(tree);
    right->height  = updateHeight(right);
    return right;
}

int IsBalanced(TREE *tree){
    if(tree != NULL)
        return getHeight(tree->right) - getHeight(tree->left);
    else
        return 0;
}

TREE*balance(TREE*tree){
    updateHeight(tree);
    int balance = IsBalanced(tree);
    if(balance==-2){
        if(IsBalanced(tree->left) == 1)
            tree->left = leftTurn(tree->left);
        return rightTurn(tree);
    }
    else if(balance == 2){
        if(IsBalanced(tree->right) == -1)
            tree->right = rightTurn(tree->right);
        return leftTurn(tree);
    }
    return tree;
}


TREE*insert(TREE* tree, int value, TREE *nodes){
    if(tree == NULL){
        return create( value,nodes,0);
    }
    if(value < tree->value)
        tree->left = insert(tree->left,value, nodes);
    else
        tree->right = insert(tree->right,value, nodes);
    tree->height = updateHeight(tree);
    return balance(tree);
}

#endif