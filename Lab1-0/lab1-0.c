#include <stdio.h>
#include <malloc.h>
#include <strings.h>


#define SAMPLE_LEN (16 + 1)


void filltable(char *smpl, int *table, int len){    //filling table of sample
    table[len - 1] = len - 1;
    for(int i = len - 2; i >= 0; i--){
        if(strrchr(smpl,smpl[i]) - smpl == i)
            table[i] = len - i - 1;
        else
            table[i] = table[strrchr(smpl,smpl[i]) - smpl];
    }
}


int move(int *table, int ind, char *smpl, char symbol){                                  //moving the sample
    if (strchr(smpl,symbol) == NULL && ind == strlen(smpl) - 1 || ind == 0)
        return strlen(smpl);
    else if(strchr(smpl,symbol) == NULL && ind != strlen(smpl) - 1)
        return table[strlen(smpl) - 1];
    else{
        return table[strchr(smpl,symbol)-smpl];
    }
}


int cmprsn(int *table,char *text,char *smpl, int textIndex) {  //comparing sample with text
    int currIndex = textIndex, i;

    for (i = strlen(smpl) - 1; i >= 0; i--) {
        if (smpl[i] == text[currIndex]){
            printf("%d ", currIndex + 1);
            if(i != 0)
                currIndex--;
            else
                return textIndex + strlen(smpl);
        }
        else {
            printf("%d ", currIndex + 1);
            currIndex = textIndex + move(table, i, smpl, text[currIndex]);
            return currIndex;
        }
    }
}


int main() {
    char smpl[SAMPLE_LEN], *text;
    int txtSize = 1, txtChar;

    gets(smpl);
    int LenSmpl = strlen(smpl);
    text = (char *) malloc(1 * sizeof(char));
    txtChar = getc(stdin);

    while (txtChar != EOF) {
        text[txtSize - 1] = (char) txtChar;
        txtChar = getc(stdin);
        txtSize++;
        text = (char *) realloc(text, txtSize * sizeof(char));
    }

    int textIndex;

    textIndex = LenSmpl - 1;

    int *table = (int *) malloc(strlen(smpl) * sizeof(int));
    filltable(smpl, table, strlen(smpl));

    if (txtSize - 1 == 0)
        return 0;

    while (textIndex < txtSize-1) {
        textIndex = cmprsn(table,text,smpl,textIndex) ;
    }
}