#include <stdio.h>

int main(  int args ,char **path ){
   FILE *file = fopen(path[0],"r");

   //checking 
   if(file==NULL){
      printf("\nfile not founded!\n");
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
