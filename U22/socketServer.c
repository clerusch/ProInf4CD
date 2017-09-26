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

int main(void){
    //Variablen
    int sock, sock2, len;
    socklen_t t;
    struct sockaddr_un local, remote;
    char str[100];

    if((sock=socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ){
        fprintf(stderr, "Error Socket erstellung\n");
        return EXIT_FAILURE;
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(sock, (struct sockaddr *)&local, len) == -1) {
        fprintf(stderr, "Error Bind\n");
        return EXIT_FAILURE;
    }

    if (listen(sock, 3) == -1) {
        fprintf(stderr, "Error listen\n");
        return EXIT_FAILURE;
    }


    while(1){
        int done, n;
        fprintf(stdout, "Auf Verbindung warten!\n");
        t = sizeof(remote);
        if ((sock2 = accept(sock, (struct sockaddr *)&remote, &t)) == -1) {
            fprintf(stderr, "Error Accept\n");
            return EXIT_FAILURE;
        }
        fprintf(stdout, "Verbindung hergestellt!\n");
        done  = 0;
        while (!done){
            n = recv(sock2, str, 100, 0);
            if (n <= 0) {
                if (n < 0){
                    fprintf(stderr, "Error recv");
                }
                done = 1;
           }

           if (!done){
               if (send(sock2, str, n, 0) < 0) {
                   fprintf(stderr, "Error send\n");
                   return EXIT_FAILURE;
               }
           }
        }

    }

    return EXIT_SUCCESS;




}
