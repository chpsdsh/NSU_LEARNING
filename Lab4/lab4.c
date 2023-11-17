#include <stdio.h>
#include <malloc.h>
#define LIST struct list

LIST{
    int key;
    int value;
    int *next;
};

