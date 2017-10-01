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
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_PATH "com_socket"
#define END "QUIT\n"


int main(void){
    //Variablen
    int sock, sock2, sock3;
    socklen_t t;
    struct sockaddr_in local;
    struct sockaddr_storage remote;
    char str[32];

    if((sock=socket(PF_INET, SOCK_STREAM, 0)) == -1 ){
        fprintf(stderr, "Error Socket erstellung\n");
        return EXIT_FAILURE;
    }

    local.sin_family = AF_INET;
    local.sin_port = htons(25300);

    local.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(local.sin_zero, '\0', sizeof local.sin_zero);
;
    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == -1) {
        fprintf(stderr, "Error Bind\n");
        return EXIT_FAILURE;
    }

    if (listen(sock, 3) == -1) {
        fprintf(stderr, "Error listen\n");
        return EXIT_FAILURE;
    }

    int done, n;
    while(1){

        fprintf(stdout, "Auf Verbindung warten!\n");
        t = sizeof(remote);
        if ((sock2 = accept(sock, (struct sockaddr *)&remote, &t)) == -1) {
            fprintf(stderr, "Error Accept\n");
            return EXIT_FAILURE;
        }
        fprintf(stdout, "Verbindung hergestellt!\n");

        if ((sock3 = accept(sock, (struct sockaddr *)&remote, &t)) == -1) {
            fprintf(stderr, "Error Accept\n");
            return EXIT_FAILURE;
        }

        fprintf(stdout, "Verbindung hergestellt!\n");
        fprintf(stdout, "\nSTART\n");
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
               if (strcmp(str, END)==0){
                   printf("CLOSE\n");
                   close(sock2);
                   done = 1;
               }
               else{
                    if (send(sock2, str, n, 0) < 0) {
                    fprintf(stderr, "Error send\n");
                    return EXIT_FAILURE;
                    }
               }
           }
           //Sock3
           n = recv(sock3, str, 100, 0);
           if (n <= 0) {
               if (n < 0){
                   fprintf(stderr, "Error recv");
               }
               done = 1;
          }

          if (!done){
              if (strcmp(str, END)==0){
                  printf("CLOSE\n");
                  close(sock3);
                  done = 1;
              }
              else{
                   if (send(sock3, str, n, 0) < 0) {
                   fprintf(stderr, "Error send\n");
                   return EXIT_FAILURE;
                   }
              }
          }





        }

    }

    return EXIT_SUCCESS;
}
