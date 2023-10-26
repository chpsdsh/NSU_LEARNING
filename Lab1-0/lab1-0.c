#include <stdio.h>
#include <malloc.h>
#include <strings.h>

#define SAMPLE_LEN (16 + 1)

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
    char smpl[SAMPLE_LEN], *text ,txtChar;
    int *table, txtSize = 1;

    gets(smpl);
    int LenSmpl = strlen(smpl);
    text = (char*)malloc(1*sizeof(char));
    txtChar = getc(stdin);
    while(txtChar != EOF){
        text[txtSize - 1] = txtChar;
        txtChar = getc(stdin);
        txtSize++;
        text = (char*)realloc(text,txtSize * sizeof(char));
    }

    table = (int*)malloc(strlen(smpl)*sizeof(int));
    filltable(smpl,table,LenSmpl);

    int currIndex, textIndex, LenText = strlen(text);
    currIndex = LenSmpl - 1;
    textIndex = LenSmpl;

    while (textIndex < LenText){
        for(int i = LenSmpl - 1; i >= 0; i--)
            if(smpl[i] == text[currIndex] ){
                printf("%d ",currIndex + 1);
                currIndex--;
                if((textIndex == LenText - 1||currIndex == LenText - 1) && (i == 0 || i== LenSmpl - 1))
                    return 0;
            }
            else {
                printf("%d ",currIndex + 1);

                if(strrchr(smpl,text[currIndex]) == NULL)
                    currIndex = textIndex + table[LenSmpl - 1] - 1;
                else
                    currIndex = textIndex + table[strrchr(smpl,text[currIndex])-smpl];

                textIndex = currIndex;
                break;
            }

    }
    }
