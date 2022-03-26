#include <dirent.h> 
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>

#define SIZE 256
void getcw(){
    char cwd[256];


    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
    else
      printf("current working directory is: %s\n", cwd);
}
void parseSpace(char* str, char** parsed)//spliting input string 
{
    int i;

    for (i = 0; i < 4; i++) {
        parsed[i] = strsep(&str, " ");
  
      
        
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}
int ownCmdHandler(char* parsed[SIZE],char inputString[SIZE])//Collection of commands
{
    int switchOwnArg;
    int NoOfOwnCmds = 6;
    char* ListOfOwnCmds[NoOfOwnCmds];
    
  
    ListOfOwnCmds[0] = "EXIT";
    ListOfOwnCmds[1] = "ECHO";
    ListOfOwnCmds[2] = "HELP";
    ListOfOwnCmds[3] = "TCP";
    ListOfOwnCmds[4] = "LOCAL";
    ListOfOwnCmds[5] = "DIR";
     for ( int i = 0; i < 6; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i ;
            break;
        }
    }
     
    switch (switchOwnArg) {
    case 0:
        printf("Bye");
        exit(0);
    case 1:
            for ( int i = 1; i < 4; i++) {
            if(parsed[i]!=NULL){
                printf("%s ",parsed[i]);
            }
           
            }
      return 1;
    case 2:
        
        return 1;
    case 3: 
       
        return 1;
     case 4: 
       
        return 1;
     case 5: ; 
        DIR* dObj;
       struct dirent* dir;
     char cwd[256];


    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
    else
      printf("current working directory is: %s\n", cwd);
     dObj = opendir(cwd);
      printf("\nList of files and sub directories: \n");
     if (dObj != NULL) {
         while ((dir = readdir(dObj)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(dObj);
        }
   
        return 1;
     case 6: 
       
        return 1;
    default:
        break;
    }
  
    return 0;
}
void inputcommand(char in[SIZE]) {//input string 
    
      scanf("%[^\n]s",in);
}     
int main()
{
    char inputString[SIZE];
    char * inputspace[SIZE];
    printf("yes master\n");
    getcw();
    inputcommand(inputString);
    parseSpace(inputString,inputspace);
    ownCmdHandler(inputspace,inputString);
  
      
       
       
   
    return 0;
}

