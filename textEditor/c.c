#include <stdio.h>

int main(  int args ,char **path ){//not complited
   path="textFile.txt";
   FILE *file = fopen(path,"r");

   //checking 
   if(file==NULL){
      printf("\nfile not founded!");
      return 1;
   }

   char c;
   int count=0;
   char *temp;
   
   printf("1");
   // while(1)
   // {
   //    //checking for ending of file
   //    if(feof(file))break;

   //    c=fgetc(file);
   //    //if char is not space
   //    if(c!='\t'&&c!=' '&&c!='\n'){
   //        temp[count]=c;
   //        count++;
   //    }
   // }
   // fclose(file);
   // //edit the file
   // file =fopen("textFile.txt","w");
   // fputs(temp,file);
   // fclose(file);
   // printf("%s",temp);
   


   return 0;
}