#include <stdio.h>

int main(  int args ,char **path ){
   FILE *file = fopen(path[0],"r");

   //checking 
   if(file==NULL){
      fprintf(stderr,"no such file or directory: %s",path[0]);
      return 1;
   }

  char line[200]; 
  int lineCount=0;
  while(fgets(line,sizeof(line),file)){
   lineCount++;
  }
  printf("%d",lineCount);
  printf("\n");
   return 0;
}
