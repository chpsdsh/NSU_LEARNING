#include <stdio.h>
#include <malloc.h>


void swap(int *arr, int ind1, int ind2){
    int tmp;
    tmp = arr[ind1];
    arr[ind1] = arr[ind2];
    arr[ind2] = tmp;
}


int partition(int *arr, int low, int high) {
    int pivot = arr[(low + high) / 2];
    int i = low , j = high ;
    while (1) {
        while (arr[i] < pivot)
            i++;

        while (arr[j] > pivot)
            j--;

        if (i >= j)
            return j;

        swap(arr, i, j);
        i++;
        j--;
    }
}


void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p);
        quickSort(arr, p + 1, high);
    }
}


int main(){
    int len;

    scanf_s("%d",&len);
    int *arr = (int*)malloc(len*sizeof(int));
    for(int i = 0; i < len; i++)
        scanf_s("%d",(arr + i));

    quickSort(arr, 0,len-1);

    for(int i = 0; i < len; i++)
        printf("%d ",arr[i]);
    free(arr);
    return 0;
}