
#include <stdio.h>
#include <malloc.h>
#include <strings.h>

#define SAMPLE_LEN 16

void filltable(char *smpl, int *table, int len){
    table[len - 1] = len;
    for(int i = len-2; i >= 0; i--){
        if(strrchr(smpl,smpl[i]) - smpl == i)
            table[i] = len - i - 1;
        else
            table[i] = table[strrchr(smpl,smpl[i]) - smpl];
    }
}


int main(){
    char smpl[SAMPLE_LEN], *text = (char*) malloc(sizeof(char));
    int *table;

    gets(smpl);
    //gets(text);
    int smpllen = strlen(smpl);

    table = (int*)malloc(strlen(smpl)*sizeof(int));
    filltable(smpl,table,strlen(smpl));
    int shift = strlen(smpl);
    int txtLen = 0;
    int *cmprsns = (int*)(malloc(sizeof(int))), cmprsnsLen = 1;
    for(;;){
        for(int i = 0; i < shift; i++){
            text[txtLen] = getchar();
            txtLen++;
            text =(char*)realloc(text,txtLen * sizeof(char));
        }
        for (int i = txtLen - 1 , j = smpllen - 1; i > txtLen - smpllen; i--,j--){
            if(text[i] == smpl[j]){
                cmprsns[cmprsnsLen - 1] = i + 1;
                cmprsns = (int*)realloc(cmprsns,cmprsnsLen * sizeof(int));
                cmprsnsLen++;
            }
            else{
                cmprsns[cmprsnsLen - 1] = i + 1;
                cmprsns = (int*)realloc(cmprsns,cmprsnsLen * sizeof(int));
                cmprsnsLen++;
                if(strrchr(smpl,text[i]) != NULL)
                    shift += table[strrchr(smpl,text[i]) - smpl];
                else
                    shift += table[strlen(smpl)];
                break;
            }

        }




    }
}
