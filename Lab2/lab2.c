#include <stdio.h>
#include <malloc.h>
#include <string.h>


int Check(char *P){
    for(int i = 0; i < strlen(P); i++)    //Check for bad input
        if (P[i] < '0' || P[i] > '9' || strchr(P,P[i]) - P != i)
            return 0;
    return 1;
}


int SearchDecr(char *P){ //finds decreasing number
    for(int i = strlen(P) - 1; i > 0; i--)
        if(P[i] > P[i-1])
            return i - 1;
    return -1;
}


int MinInMax(char* P, int RearrNom){  //finds MINIMUM IN MAXIMUMS
    int RearrNomValue = '0' + (int)P[RearrNom], min = 999, index = 0;
    for(int i = RearrNom + 1; i< strlen(P); i++)
        if('0' + P[i] > RearrNomValue && '0' + P[i] < min){
            min = '0' + P[i];
            index = i;
        }
    return index;
}


void reverse(char *P, int RearrNom){ //REVERSES TAIL
        char tmp;
        for(int i = RearrNom + 1 , p = 0; p < (strlen(P)-RearrNom - 1)/2; i++, p++){
            tmp = P[i];
            P[i] = P[strlen(P) - p - 1];
            P[strlen(P) - p - 1] = tmp;
        }
    }


void rearrangement(char *P, int N){ //REARRANGES SUBSEQUENCE
    int RearrNom, indexMinInMax;
    char tmp;
    for (int i = 0; i < N; i++){
        RearrNom = SearchDecr(P);
        if(RearrNom == -1){
            exit(0);
        }
        indexMinInMax = MinInMax(P,RearrNom);
        tmp = P[RearrNom];
        P[RearrNom] = P[indexMinInMax];
        P[indexMinInMax] = tmp;
        reverse(P,RearrNom);
        printf("%s\n",P);

    }
}


int main(){
    char P[100];
    int N;
    gets(P);
    scanf("%d",&N);
    if(Check(P) == 0){
        printf("bad input");
        return 0;
    }
    rearrangement(P,N);
    return 0;
}
