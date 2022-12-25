#include <stdio.h>

int main(  int args ,char **path ){
   
   FILE *file = fopen(path[0],"r");

   //checking 
   if(file==NULL){
      fprintf(stderr,"no such file or directory: %s",path[0]);
      return 1;
   }

   char c;
   int count=0;
   char temp[1000];
   
   while(1)
   {
      //checking for ending of file
      if(feof(file))break;

      c=fgetc(file);
      //if char is not space
      if(c!='\t'&&c!=' '&&c!='\n'){
          temp[count]=c;
          count++;
      }
   }
   temp[count]=0;
   fclose(file);
   //edit the file
   file =fopen(path[0],"w");
   fputs(temp,file);
   fclose(file);
   printf("%s",temp);
   
   printf("\n");
   


   return 0;
}
