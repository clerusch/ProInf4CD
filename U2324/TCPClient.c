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
#define buffSize 100

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

    while (printf("Client> "), fgets(buff, buffSize, stdin), !feof(stdin)){ //KommaOperator ist krass
        if (send(sock, buff, buffSize, 0)==-1){
            fprintf(stderr, "Error Client beim senden\n");
            return EXIT_FAILURE;
        }
        if ((t=recv(sock, buff, buffSize, 0 ))>0){
            buff[t]='\0';
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

    }



    return EXIT_SUCCESS;
}
