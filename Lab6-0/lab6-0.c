#include <stdio.h>
#include "avltree.h"

int main() {
    FILE *file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }
    int N;
    fscanf(file, "%d", &N);
    if (N == 0) {
        puts("0");
        fclose(file); // Закрываем файл
        return 0;
    }
    int *values = (int*) malloc((N)*sizeof(int));

    for (int i = 0; i < N; i++) {
        fscanf(file, "%d", &values[i]);
    }
    printf("%d", FillTree(values,N)->height + 1);
    free(values);
    fclose(file); // Закрываем файл
    return 0;
}
