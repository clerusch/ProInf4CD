//weil Clemens es vergisst
//Dominik & Clemens
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_PATH "com_socket"
#define buffSize 16
#define START "START\n"

int main (void){
    int sock, t;

    char buff[buffSize];
    struct sockaddr_in remote;
    socklen_t addr_size;


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Error Client Socket erstellung\n");
        return EXIT_FAILURE;
    }

    remote.sin_family = AF_INET;
    remote.sin_port = htons(25300);
    remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(remote.sin_zero, '\0', sizeof remote.sin_zero);
    addr_size = sizeof(remote);
    if  (connect(sock, (struct sockaddr *) &remote, addr_size) == -1){
        fprintf(stderr, "Error Client connect\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Verbindung erfolgreich!\n");

    while (1){
        //clear buff
        memset(buff, 0, buffSize);
        do{
            fprintf(stdout,"Warten auf Serverstarsignal\n");
            if ((t=recv(sock, buff, buffSize, 0 ))<0){
                fprintf(stderr, "Error Client Socket erstellung\n");
                return EXIT_FAILURE;
            }
        }
        while(strcmp(buff, "START\n")!=0);
        //Eingabe des Benutzers
        while(1){
            fprintf(stdout, "Spiel gestartet\nSCHERE, STEIN oder PAPIER - QUIT zum Beenden\n");
            printf("vor fgels\n");
            fgets(buff, buffSize, stdin);
            fprintf(stdout, "nach fgets %s ", buff);
            if ( (strcmp(buff,"SCHERE\n")==0) || (strcmp(buff,"STEIN\n")==0) || (strcmp(buff, "PAPIER\n")==0) ){
                printf("if");
                break;
            }
            else if(strcmp(buff, "QUIT\n")==0) {
                printf("else if");
                if (send(sock, buff, buffSize, 0)==-1){
                    printf("else if if");
                    fprintf(stderr, "Error Client beim senden\n");

                    return EXIT_FAILURE;
                }
                close(sock);
                return EXIT_SUCCESS;
            }
            else{
                fprintf(stdout, "Falsche Eingabe\n");
            }
        }
                printf("77\n");

        if (send(sock, buff, buffSize, 0)==-1){
            fprintf(stderr, "Error Client beim senden\n");
            return EXIT_FAILURE;
        }
        printf("gesendet %s\n", buff);
        if ((t=recv(sock, buff, buffSize, 0 ))>0){
            //buff[t]='\0';
            printf(buff);
            fprintf(stdout, "Server> %s\n", buff);
        }

        else{
            if (t<0){
                fprintf(stderr, "Error Client Socket erstellung\n");
                return EXIT_FAILURE;
            }
            else{
                fprintf(stdout, "Server Verbindung beendet\n");
                return EXIT_SUCCESS;
            }
        }
                printf("NACH IF ELSE");
    }



    return EXIT_SUCCESS;
}
