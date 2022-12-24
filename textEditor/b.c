#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <ctype.h>
   
int main(int args,char **path)  
{     
    FILE *file;  
    char ch, *line;  
    size_t len = 0, read;  
    char words[1000][1000], word[20];  
    int i = 0, j, k, maxCount = 0, count;  
      
    //Opens file in read mode  
    file = fopen(path[0],"r");  
      
    //If file doesn't exist  
    if (file == NULL){  
        printf("File not found");  
        return(1);
    }  
      
    //Since, C doesn't provide in-built function,   
    //following code will split content of file into words  
    while ((read = getline(&line, &len, file)) != -1) {  
          
        for(k=0; line[k]!='\0'; k++){  
            //Here, i represents row and j represents column of two-dimensional array words   
            if(line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.' ){  
                words[i][j++] = tolower(line[k]);  
            }  
            else{  
                words[i][j] = '\0';  
                //Increment row count to store new word  
                i++;  
                //Set column count to 0  
                j = 0;  
            }  
        }  
    }  
      
    int length = i;  
      
    //Determine the most repeated word in a file  
    for(i = 0; i < length; i++){  
        count = 1;  
        //Count each word in the file and store it in variable count  
        for(j = i+1; j < length; j++){  
            if(strcmp(words[i], words[j]) == 0 && (strcmp(words[i]," ") != 0)){  
                count++;  
            }   
        }  
        //If maxCount is less than count then store value of count in maxCount   
        //and corresponding word to variable word  
        if(count > maxCount){  
            maxCount = count;  
            strcpy(word, words[i]);  
        }  
    }  
      
    printf("%s", word); 
    
    printf("\n"); 
    fclose(file);  
      
    return 0;  
} 
