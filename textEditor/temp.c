#include <stdio.h>
#include <unistd.h>
#include <string.h>
void printprompt(){
}
int main(){
   char path[]="/Users/mehrdadhadidian/Documents/programing/excuteTest/fpl";
   
  char *argv[] = {   "/Users/mehrdadhadidian/Documents/programing/excuteTest/textFile.txt", 0 };
  execv(path,argv);

return 0 ;

}