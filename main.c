#include <dirent.h> 
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>

#define SIZE 256

int CommunicationFlag = 0;

void PrintOnWhere(char a[SIZE]){
    if (CommunicationFlag==0){
        printf("Sending Client ..%s\n", a);
    }else{
        printf("Sending TCP .. %s\n", a);
    }
}


void getcw(){
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL){
      perror("getcwd() error");
    }
    else{
        PrintOnWhere(cwd);
    }
}


void parseSpace(char* str, char** parsed)//spliting input string 
{
    int i;
    for (i = 0; i < 4; i++) {
        parsed[i] = strsep(&str, " ");
        if (parsed[i] == NULL){
            break;
        }
        if (strlen(parsed[i]) == 0){
            i--;
        }
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
            PrintOnWhere("Bye");
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
            CommunicationFlag = 1;
            return 1;
        case 4: 
            CommunicationFlag = 0;
            return 1;
        case 5: ; 
            DIR* dObj;
            struct dirent* dir;
            char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
   
     dObj = opendir(cwd);
     PrintOnWhere("\nList of files and directories:\n");
     if (dObj != NULL) {
         while ((dir = readdir(dObj)) != NULL) {
            PrintOnWhere(dir->d_name);
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
    //printf("111111111111111111111111111111111111\n");
    scanf("%[^\n]s",in);
    
}



int main()
{ 
    
     char inputString[SIZE];
    char * inputspace[SIZE];
    
   
    while(1){
    fflush(stdout);
    scanf("%[^\n]s",inputString);
      while ((getchar()) != '\n');
    printf("%s",inputString);
   
    printf("yes master\n");
    getcw();
    
   
    parseSpace(inputString,inputspace);
    ownCmdHandler(inputspace,inputString);  
      
       
    }
    return 0;
}