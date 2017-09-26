//weil Clemens es vergisst
//Dominik & Clemens
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "com_socket"
#define buffSize 100

int main (void){
    int sock, len, t;
    struct sockaddr_un remote;
    char buff[buffSize];


    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Error Client Socket erstellung\n");
        return EXIT_FAILURE;
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if  (connect(sock, (struct sockaddr *) &remote, len) == -1){
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
