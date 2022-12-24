#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
// #include<readline/history.h>
//  #include <readline/readline.h>

#define MAXLIST 100

char TEdir[200];
char Hi2dir[200];
int itsLinux=1;

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
void addToHistory(char *str){

    FILE *file = fopen(Hi2dir,"r+");
    //checking
    if(file==NULL){
        printf(stderr,"\nhistory file not founded!");
        return ;
    }

    char line[50][200];
    int linCounter=0;
    // history
    while(fgets(line[linCounter],sizeof(line),file)){
        linCounter++;
    }
    fclose(file);
    file = fopen(Hi2dir,"w");

    fputs(str,file);
    fputs("\n",file);

    for(int i=0;i<linCounter;i++){
        fputs(line[i],file);

    }
    fclose(file);
}
void showHistory(){
    FILE *file = fopen(Hi2dir,"r");
    //checking
    if(file==NULL){
        printf(stderr,"\nhistory file not founded!");
        return ;
    }

    char line[200];

    //printing history
    while(fgets(line,sizeof(line),file)){
        printf("%s",line);
    }
    fclose(file);
}

int readLine(char* str){
    int n = MAXLIST;
    char * buf = malloc(sizeof(char) * n);
    getline(&buf, &n, stdin);

    if (strlen(buf) != 0) {
        strcpy(str, buf);
        trimtrailing(str);
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
int parsePipes(char* str,char** pipedArgs){
    int i = 0;
    char arr[MAXLIST];
    int length = strlen(str);
    while(i< MAXLIST){
        arr[i++] = *str;
        str++;
    }
    char *token = strtok(arr,"|");
    printf("%S",token);
    if(strlen(token)==length)
        return 1;
    i = 0;
    while(i<MAXLIST){
        pipedArgs[i] = token;
        if (pipedArgs[i] == NULL)
            break;
        token = strtok(NULL,"|");
        i++;
    }

    return 0;
}
void execute(char* command, char** args){

    //text edit commands
    if(!strcmp("a",command)||!strcmp("b",command)||!strcmp("c",command)||
       !strcmp("d",command)||!strcmp("f",command)||!strcmp("g",command)){

        char pathCopy[200];
        strcpy(pathCopy,TEdir);
        strcat(pathCopy,command);
        if(itsLinux){
            strcat(pathCopy,".out");
        }
        int filePathSize  = 1024;
        char filePath[filePathSize];
        getcwd(filePath, filePathSize);
        strcat(filePath,"/");
        strcat(filePath,args[1]);
        char *argv[] = {   filePath, 0 };
        pid_t pid;
        pid = fork();
        if (pid == -1) {
//            stderr("");
        }
        if (pid == 0) {
            if(execv(pathCopy,argv)<0)
            fprintf( stderr,"couldn't execute command\n");
        } else
            waitpid(pid, 0, 0);
    }

    //history command
    else if(!strcmp("his",command)){
        showHistory();
    }
    else if(strcmp("cd",command) == 0){
        chdir(args[1]);
    }
    else {
        pid_t pid;
        pid = fork();
        if (pid == -1) {
            fprintf( stderr,"failed to fork");
        }
        if (pid == 0) {
            if(execvp(command, args)<0);
                fprintf( stderr,"couldn't execute command\n");
            exit(0);
        } else
            waitpid(pid, 0, 0);
    }


}

void executePipe(char** pipeArgs){
    char* args[MAXLIST];
//    parseArgs(pipeArgs[0],args);
//    execute(args[0],args);
    int fd[2];
    if(pipe(fd)==-1)
        fprintf( stderr,"failed to create pipe\n");
    int pid1 = fork();
    if(pid1<0){}
    if(pid1==0){
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        parseArgs(pipeArgs[0],args);
        execute(args[0],args);
        exit(0);

    }
    int pid2 = fork();
    if(pid2<0){}
    if(pid2==0){
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        parseArgs(pipeArgs[1],args);
        execute(args[0],args);
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);

}
void printPrompt(){
    int addressSize  = 1024;
    char address[addressSize];
    getcwd(address, addressSize);
    printf("%s>>>", address);
}

void directorySetUp(){
    if(itsLinux){
        chdir("..");
    }

    getcwd(TEdir,sizeof(TEdir));
    strcpy(Hi2dir,TEdir);
    strcat(TEdir,"/textEditor/");
    strcat(Hi2dir,"/history/history.txt");
    //clear history file
    FILE *file = fopen(Hi2dir,"w");
    fprintf(file,"");
    fclose(file);
}
int main() {

    directorySetUp();
    char* args[MAXLIST];
    char* pipeArgs[MAXLIST];
    char str[MAXLIST];


    while(1){
        printPrompt();
        readLine(str);
        addToHistory(str);
        if(parsePipes(str,pipeArgs) == 1) {
            parseArgs(str, args);
            execute(args[0],args);
        }
        else{
            executePipe(pipeArgs);
        }
    }
    return 0;
}

