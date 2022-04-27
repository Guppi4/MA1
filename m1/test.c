#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 256

int CommunicationFlag;
int welcomeSocket, newSocket;
char buffer[1024];
struct sockaddr_in serverAddr;
struct sockaddr_storage serverStorage;
socklen_t addr_size;


void PrintOnWhere(char a[SIZE]) {
    if (CommunicationFlag == 0) {
        printf("\nNO TCP - %s\n", a);
    } else {
        welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(7891);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
        bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
        if (listen(welcomeSocket, 10) == 0) {
            printf("Listening..\n");
        } else {
            printf("Socket error\n");
        }
        addr_size = sizeof serverStorage;
        newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
        strcpy(buffer, a);
        send(newSocket, buffer, 13, 0);
        close(welcomeSocket);
        close(newSocket);
    }
}
void getcw() {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
    }
    else {
        PrintOnWhere(cwd);
    }
}
void parseSpace(char* str, char** parsed)//spliting input string
{
    int i;
    for (i = 0; i < 4; i++) {
        parsed[i] = strsep(&str, " ");
        if (parsed[i] == NULL) {
            break;
        }
        if (strlen(parsed[i]) == 0) {
            i--;
        }
    }
}
int ownCmdHandler(char* parsed[SIZE], char inputString[SIZE]) //Collection of commands
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
    ListOfOwnCmds[6] = "COPY";
    ListOfOwnCmds[7] = "CD";
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
            if (parsed[i] != NULL) {
                printf("%s\n", parsed[i]);
            }
        }
        getcw();
        return 1;
    case 2:

        return 1;
    case 3:
        CommunicationFlag = 1;
        getcw();
        return 1;
    case 4:
        CommunicationFlag = 0;
        getcw();
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
        //break;
        return 1;
    case 6:

        char ch;// source_file[20], target_file[20];
        FILE *source, *target;
        char source_file[]="x1.txt";
        char target_file[]="x3.txt";
        source = fopen(source_file, "r");
        if (source == NULL) {
        printf("Press any key to exit...n");
        //exit(EXIT_FAILURE);
        }
        target = fopen(target_file, "w");
        if (target == NULL) {
        fclose(source);
        printf("Press any key to exit...n");
        //exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);
        printf("File copied successfully.n");
        fclose(source);
        fclose(target);

            return 1;
        default:
            break;
        }
    return 0;
}
int main()
{
    char inputString[SIZE];
    char * inputspace[SIZE];
    printf("Yes master ?\n");
    getcw();
    while (1) {
        fflush(stdout);
        scanf("%[^\n]s", inputString);
        while ((getchar()) != '\n');
        parseSpace(inputString, inputspace);
        ownCmdHandler(inputspace, inputString);
        getcw();
    }
    return 0;
}