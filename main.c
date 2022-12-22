
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>



#define MAXLIST 100


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
int readLine(char* str){
    int n = MAXLIST;
    char * buf = malloc(sizeof(char) * n);
    getline(&buf, &n, stdin);
    if (strlen(buf) != 0) {
//        add_history(buf);
        strcpy(str, buf);
        trimtrailing(str);
        free(buf);
        return 0;
    } else {
        free(buf);
        return 1;
    }
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
//    while(1){


void execute(char* command, char** args){

    if(strcmp("cd",command) == 0){
        chdir(args[1]);
    }
    else {
        pid_t pid;
        pid = fork();
        if (pid == -1) {

        }
        if (pid == 0) {
            execvp(command, args);
            exit(0);
        } else
            waitpid(pid, 0, 0);
    }


}

void printPrompt(){
    int addressSize  = 1024;
    char address[addressSize];
    getcwd(address, addressSize);
    printf("%s>>>", address);
}


int main() {

    char* args[MAXLIST];
    char str[MAXLIST];

    while(1){
        printPrompt();
        readLine(str);
        parseArgs(str,args);
        execute(args[0],args);
    }

    return 0;
}

