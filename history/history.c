#include <stdio.h>

int main(  int args ,char *argv[] ){

   FILE *file = fopen(argv[1],"w+");
   fprintf(file,"%s",argv[0]);

   return 0;
}
