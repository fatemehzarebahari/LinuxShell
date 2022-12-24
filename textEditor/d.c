#include <stdio.h>

int main(  int args ,char **path ){
   FILE *file = fopen(path[0],"r");

   //checking 
   if(file==NULL){
      printf("\nfile not founded!\n");
      return 1;
   }

  char line[200]; 
 
  while(fgets(line,sizeof(line),file)){
   if(line[0]!='#'){
      printf("%s\n",line);

   }
  }
   return 0;
}
