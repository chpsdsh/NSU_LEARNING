#include <malloc.h>
#include <stdio.h>

void errorCheck(short int NodeCnt,short int Start,short int Finish,int EdgeCnt){
    if (NodeCnt < 0 || NodeCnt > 5000){
        puts("bad number of vertices");
        exit(0);
    }
    if (EdgeCnt < 0 || EdgeCnt > NodeCnt*(NodeCnt+1)/2){
        puts("bad number of edge");
        exit(0);
    }
    if (Start < 0 || Start > NodeCnt || Finish < 0 || Finish > NodeCnt ){
        puts("bad vertex");
        exit(0);
    }
    if (NodeCnt < 0 || NodeCnt > INT_MAX){
        puts("bad length");
        exit(0);
    }
}

int main() {
    FILE *file = fopen("in.txt", "r");

    int NodeCnt,Start,Finish,EdgeCnt;
    if(!fscanf(file, "%d", &NodeCnt)){
        fclose(file);
        return 0;
    }
    if(fscanf(file, "%d %d", &Start,&Finish)!=2){
        fclose(file);
        return 0;
    }
    if(!fscanf(file, "%d", &EdgeCnt)){
        fclose(file);
        return 0;
    }

    fclose(file);
}