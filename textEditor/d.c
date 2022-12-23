#include <stdio.h>

int main(  int args ,char **path ){
   FILE *file = fopen(path,"r");

   //checking 
   if(file==NULL){
      printf("\nfile not founded!");
      return 1;
   }

  char line[50]; 
 
  while(fgets(line,sizeof(line),file)){
   if(line[0]!='#'){
      printf("%s",line);
   }
  }
   return 0;
}