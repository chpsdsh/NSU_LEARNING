#include <malloc.h>
#include <stdio.h>



int main() {
    FILE *file = fopen("in.txt", "r");

    int NodeCnt,Start,Finish,EdgeCnt;
    if(!fscanf(file, "%d", &NodeCnt)){
        fclose(file);
        return 0;
    }



    fclose(file);
}