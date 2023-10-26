#include <stdio.h>
#include <malloc.h>
#include <strings.h>

#define SAMPLE_LEN (16 + 1)

void filltable(char *smpl, int *table, int len){
    table[len - 1] = len-1;
    for(int i = len-2; i >= 0; i--){
        if(strrchr(smpl,smpl[i]) - smpl == i)
            table[i] = len - i - 1;
        else
            table[i] = table[strrchr(smpl,smpl[i]) - smpl];

    }

}


int move(int ind, char *smpl, char symbol){
    int *table = (int *) malloc(strlen(smpl) * sizeof(int));
    filltable(smpl, table, strlen(smpl));

    if (strchr(smpl,symbol)==NULL && ind == strlen(smpl) - 1)
        return strlen(smpl);
    else if(strchr(smpl,symbol)==NULL && ind != strlen(smpl) - 1)
        return table[strlen(smpl)-1];
    else
        return table[strrchr(smpl,symbol)-smpl-1] - 1;

}


int cmprsn(char *text,char *smpl, int textIndex) {
    int currIndex = textIndex ,i;
    for (i = strlen(smpl) - 1; i >= 0; i--){
        if(smpl[i] == text[currIndex]){
            printf("%d ",currIndex + 1);
            currIndex--;
            if(currIndex==-1){
                currIndex = textIndex + strlen(text);
                return currIndex;
            }

        }
        else{
            printf("%d ",currIndex + 1);
            currIndex = textIndex + move(i,smpl,text[currIndex]);
            return currIndex;
        }
    }



    if (textIndex+1 == strlen(text))
        exit(0);
}

int main() {
    char smpl[SAMPLE_LEN], *text, txtChar;
    int txtSize = 1;

    gets(smpl);
    int LenSmpl = strlen(smpl);
    text = (char *) malloc(1 * sizeof(char));
    txtChar = getc(stdin);

    while (txtChar != EOF) {
        text[txtSize - 1] = txtChar;
        txtChar = getc(stdin);
        txtSize++;
        text = (char *) realloc(text, txtSize * sizeof(char));
    }

    int textIndex;

    textIndex = LenSmpl - 1;

    if (txtSize - 1 == 0) {
        return 0;
    }

    while (textIndex < txtSize) {
        textIndex = cmprsn(text,smpl,textIndex) ;
    }
}

