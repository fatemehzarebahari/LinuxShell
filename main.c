
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include<readline/history.h>
#include <readline/readline.h>

#define MAXLIST 100

char TEdir[200];
char Hidir[200];
char Hi2dir[200];

void trimtrailing(char *s)
{
    int i=strlen(s)-1;
    while(i>-1)
    {
        if(s[i]==' '||s[i]=='\t'||s[i]=='\n')
            i--;
        else
            break;
    }
    s[i+1]='\0';
}
void addToHistory(char* str){
//    char *argv[] = {   str,Hi2dir, 0 };
//    execv(Hidir,argv);
    FILE *file = fopen(Hi2dir,"w");
    fprintf(file,"%s",str);
}

int readLine(char* str){
    int n = MAXLIST;
    char * buf = malloc(sizeof(char) * n);
    getline(&buf, &n, stdin);

    if (strlen(buf) != 0) {
        strcpy(str, buf);
        trimtrailing(str);
        addToHistory(str);
        free(buf);
        return 0;
    } else {
        free(buf);
        return 1;
    }
//    char* newLine;
//
//    newLine = readline("");
//    if (strlen(newLine) != 0) {
//        add_history(newLine);
//        strcpy(str, newLine);
//        addToHistory(str);
//
//        return 0;
//    } else {
//        return 1;
//    }
}

void parseArgs(char *str,char** args){
    int i = 0;
    char arr[MAXLIST];
    while(i< MAXLIST){
        arr[i++] = *str;
        str++;
    }
    char *token = strtok(arr," ");
    i = 0;
    while(i<MAXLIST){
        args[i] = token;
        if (args[i] == NULL)
            break;
        token = strtok(NULL," ");
        i++;
    }

}

void printPrompt(){
    int addressSize  = 2048;
    char address[addressSize];
    getcwd(address, addressSize);
    printf("%s-->", address);
}
void execute(char* command, char** args){
    if(!strcmp("a",command)||!strcmp("b",command)||!strcmp("c",command)||
       !strcmp("d",command)||!strcmp("f",command)||!strcmp("g",command)){
//        printf(TEdir);
        char pathCopy[200];
        strcpy(pathCopy,TEdir);
        strcat(pathCopy,command);
        strcat(pathCopy,".out");
        int filePathSize  = 1024;
        char filePath[filePathSize];
        getcwd(filePath, filePathSize);
        strcat(filePath,"/");
        strcat(filePath,args[1]);
//        puts(filePath);
        char *argv[] = {   filePath, 0 };

        execv(pathCopy,argv);
    }
    if(strcmp("cd",command) == 0){
        chdir(args[1]);
    }
    else {
        pid_t pid;
        pid = fork();
        if (pid == -1) {
            fprintf( stderr,"failed to fork");
        }
        if (pid == 0) {
            if(execvp(command, args)<0){
                fprintf( stderr,"command doesn't exist\n");
            }
            exit(0);
        } else
            waitpid(pid, 0, 0);
    }


}


void directorySetUp(){
    chdir("..");
    getcwd(TEdir,sizeof(TEdir));
    strcpy(Hidir,TEdir);
    strcpy(Hi2dir,TEdir);
    strcat(TEdir,"/textEditor/");
    strcat(Hidir,"/history/a.out");
    strcat(Hi2dir,"/history/history.txt");
}
int main() {

    directorySetUp();
    char* args[MAXLIST];
    char str[MAXLIST];


    while(1){
        printPrompt();
        readLine(str);
        addToHistory(str);
        parseArgs(str,args);
        execute(args[0],args);
    }
    return 0;
}


