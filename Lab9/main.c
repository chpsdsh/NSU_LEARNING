#include <malloc.h>
#include <stdio.h>

void errorCheck(int N,int S,int F,int M){
    if (N < 0 || N > 5000){
        puts("bad number of vertices");
        exit(0);
    }
    if (M < 0 || M > N*(N+1)/2){
        puts("bad number of edge");
        exit(0);
    }
    if (S < 0 || S > N || F < 0 || F > N ){
        puts("bad vertex");
        exit(0);
    }
    if (N < 0 || N > 5000){
        puts("bad number of vertices");
        exit(0);
    }
}

int main() {
    FILE *file = fopen("in.txt", "r");

    int N,S,F,M;
    if(!fscanf(file, "%d", &N)){
        fclose(file);
        return 0;
    }
    if(fscanf(file, "%d %d", &S,&F)!=2){
        fclose(file);
        return 0;
    }
    if(!fscanf(file, "%d", &M)){
        fclose(file);
        return 0;
    }

    fclose(file);
}