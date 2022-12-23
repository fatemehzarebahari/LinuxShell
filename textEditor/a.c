#include <stdio.h>
void printFirstPart(char *string){
   for(int i=0;string[i]!=' '&&string[i]!=0;i++){
      printf("%c",string[i]);
   }
   printf("\n");
}
int main(int args, char *path[] ){
   FILE *file = fopen(path[0],"r");
   //checking 
   if(file==NULL){
      printf("\nfile not founded!");
      return 1;
   }

  char line[200]; 

  while(fgets(line,sizeof(line),file)){
   printFirstPart(line);
  }
   return 0;
}