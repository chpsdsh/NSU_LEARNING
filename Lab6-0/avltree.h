#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H

#define TREE struct tree

#include <malloc.h>
#include <stdio.h>

int max(int h1, int h2){//returns maximum
    if (h1 >= h2)
        return h1;
    else
        return h2;
}

TREE{
    int value;
    TREE *left;
    TREE *right;
};


TREE*create(int value, TREE*arr, int counter){ //creating new nodes
    arr[counter].value = value;
    arr[counter].left = arr[counter].right = 0;
    return &arr[counter];
}


int getHeight(TREE* tree) {
    if (tree == NULL)
        return -1;

    int leftHeight = getHeight(tree->left);
    int rightHeight = getHeight(tree->right);

    return 1 + max(leftHeight, rightHeight);
}


TREE *rightTurn(TREE *tree){
    TREE*left = tree->left;

    tree->left = left->right;
    left->right = tree;


    return left;
}


TREE *leftTurn(TREE *tree){
    TREE*right = tree->right;

    tree->right = right->left;
    right->left = tree;


    return right;
}


int IsBalanced(TREE *tree){//Check for balance
    if(tree != NULL)
        return getHeight(tree->right) - getHeight(tree->left);
    else
        return 0;
}

TREE*balance(TREE*tree){//balancing tree
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


TREE*insert(TREE* tree, int value, TREE *nodes){//inserting new nodes to tree
    if(tree == NULL){
        return create( value,nodes,0);
    }
    else if(value < tree->value)
        tree->left = insert(tree->left,value, nodes);
    else
        tree->right = insert(tree->right,value, nodes);

    return balance(tree);
}


void Search(TREE* tree, int value){
    if (tree == NULL){
        puts("False");
        exit(0);
    }
    else if  (tree->value == value)
        puts("True");
    else if (tree->value > value)
        Search(tree->left,value);
    if (tree->value < value)
        Search(tree->right,value);
}

void InOrder(TREE *T) {
    if (T -> left != NULL)
        InOrder(T -> left);

    printf("%d\n", T -> value);

    if (T -> right != NULL)
        InOrder(T -> right);
}
#endif