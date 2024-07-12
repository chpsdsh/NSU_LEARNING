#include <stdio.h>
#include "tree.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int getnum(char *str){//get number from data string
    int i = 0;
    char res[10000];

    while(str[i] != '_'){
        res[i] = str[i];
        i++;
    }

    int result = atoi(res);

    return result;
}

void getAnswer(char *str){//returns correct answer
    int ind = 0, ressize = 0;
    char *res = (char*) malloc(sizeof(char));

    while(str[ind] != '?')
        ind++;

    for (int i = ind-1; str[i] != ' '; i--){
        res[ressize++] = str[i];
        realloc(res,ressize*sizeof(char));
        res[ressize] = '\0';
    }

    printf("It is");

    for(int i = strlen(res); i >= 0; i--)
        printf("%c",res[i]);
}

char *getQuestion(char *str){//gets question from data str
    int ind = 0, ressize = 0;
    char *res = (char*) malloc(sizeof(char)*1000);

    while(str[ind] != '_')
        ind++;

    for (int i = ind+1; i < strlen(str) && str[i] != '\n'; i++){
        res[i - ind - 1] = str[i];
        ressize++;
        realloc(res,ressize*sizeof(char));
        res[i+1] = '\0';

    }

    return res;
}


char* inttostr(int num) {//converts integer to string
    char *res = (char*) malloc(sizeof(char) * 12);
    int ressize = 0;

    while (num != 0) {
        res[ressize] = '0' + num % 10;
        num /= 10;
        ressize++;
        res = (char*) realloc(res, sizeof(char) * (ressize + 1));
    }

    res[ressize] = '\0';

    for (int i = 0; i < ressize / 2; i++) {
        char tmp = res[i];
        res[i] = res[ressize - 1 - i];
        res[ressize - 1 - i] = tmp;
    }

    return res;
}

void replaceString( char* str, char* new_str) {//replaces strings in data

    FILE *file = fopen("data.txt","r");
    char buffer[256];
    char **arr = NULL;
    int len = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        arr = realloc(arr, (len + 1) * sizeof(char*));
        arr[len] = strdup(buffer);
        len++;
    }

    fclose(file);
    file = fopen("data.txt","w");
    for(int i = 0;i < len; i++){
        if(strstr(arr[i],str)!=0){
            if(i+1 != len)
                fprintf(file, "%s\n",new_str);
            else
                fprintf(file, "%s",new_str);
        }
        else
            fprintf(file, "%s",arr[i]);
    }
    fclose(file);

}


char *getstring(char*str){//inputs string by symbols
    int len = strlen(str)+1;

    str[len-1] = '_';
    str[len] = '\0';
    realloc(str,len*sizeof(char));
    char s;
    s = getchar();
    while(s != '\n'){
        str[len++] = s;
        str = (char*)realloc(str, sizeof(char)*(len));
        s = getchar();
    }
    str[len] = '\0';
    return str;
}


char *createans(int nmb, char *wish, char *value, int flag){//adds new data
    char buffer[256];
    FILE *file = fopen("data.txt","r+");
    fseek(file, 0, SEEK_END);
    fgets(buffer,sizeof(buffer), file);
    fclose(file);

    file = fopen("data.txt","a");

    if(flag ==1){
        if(buffer[strlen(buffer)-1]!='\n')
            fputs("\n",file);
        fputs(inttostr(nmb*2),file);
        fputs("_Is it ",file);
        fputs(wish,file);
        fputs("?",file);
        fputs("\n",file);
        fputs(inttostr(nmb*2+1),file);
        fputs("_",file);
        fputs(value,file);
    }
    else if (flag == 0){
        if(buffer[strlen(buffer)-1]!='\n')
            fputs("\n",file);
        fputs(inttostr(nmb*2),file);
        fputs("_",file);
        fputs(value,file);
        fputs("\n",file);
        fputs(inttostr(nmb*2+1),file);
        fputs("_",file);
        fputs(wish,file);
        fputs("?",file);
    }
    fclose(file);
}


void Game(TREE *T){//game
    int game = 1;
    char answer[4];
    puts("Answer only yes/no");

    while(game){

        printf("%s\n",T->value);
        puts("Your answer:");
        scanf("%s",&answer);

        if(strcmp(answer,"yes")==0){
            if(T->left)
                T = T->left;
            else{
                getAnswer(T->value);
                exit(0);
            }
        }
        else if(strcmp(answer,"no") == 0){
            if(T->right)
                T = T->right;
            else{
                printf("What did you wish for?\n");

                char wish[256];
                scanf("%s",wish);
                printf("Ask a question to differ it from other\n");

                char *new_str = inttostr(T->nmb);
                char c = getchar();
                new_str = getstring(new_str);
                replaceString(T->value,new_str);

                puts("Answer your question:");
                scanf("%s",&answer);

                if(strcmp(answer,"yes")==0)
                    createans(T->nmb,wish,T->value,1);

                else if (strcmp(answer,"no")==0)
                    createans(T->nmb,wish,T->value,0);

                exit(0);
            }

        }
    }
}


void FileToTree(TREE *T, FILE *file){//converts file to tree
    char buffer[256];
    fgets(buffer,sizeof(buffer),file);

    char *question = getQuestion(buffer);
    T = create(question, getnum(buffer));

    while(fgets(buffer,sizeof(buffer),file) != NULL){
        question = getQuestion(buffer);
        add(T, question, getnum(buffer));
    }

    Game(T);
    free(question);
}


int main() {
    FILE *file;
    file = fopen("data.txt","r");

    TREE *T;

    if (file == NULL) {
        puts("ERROR");
        exit(0);
    }

    FileToTree(T,file);

    fclose(file);

    return 0;
}
