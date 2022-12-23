#include <stdio.h>

int main(  int args ,char **path ){
   FILE *file = fopen(path,"r");

   //checking 
   if(file==NULL){
      printf("\nfile not founded!");
      return 1;
   }

  char line[200]; 
  int count=1;

  //printing firt 10 lines
  while(fgets(line,sizeof(line),file)&&count<11){
   printf("%s",line);

   count++;
  }
   return 0;
}