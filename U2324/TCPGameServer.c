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
#define START "START\n"

int p1vsp2(char p1[], char p2[]){
    if(strcmp(p1, p2)==0){
        return 0;
    }
    if(strcmp(p1, "PAPIER\n")==0 && strcmp(p2, "STEIN\n")==0){
        return 1;
    }
    if(strcmp(p1, "SCHERE\n")==0 && strcmp(p2, "PAIER\n")==0){
        return 1;
    }
    if(strcmp("STEIN\n", p1)==0 && strcmp(p2, "SCHERE\n")==0){
        return 1;
    }
    return 2;
}

int main(void){
    //Variablen
    int sock, sock2, sock3;
    socklen_t t;
    struct sockaddr_in local;
    struct sockaddr_storage remote;
    char str[32],str2[32];

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

    int done, n, i, answer;
    char s2A = 0;
    char s3A = 0;
    while(1){

        fprintf(stdout, "Auf Verbindung warten!\n");
        t = sizeof(remote);
        if (s2A == 0){
            s2A = 1;
            if ((sock2 = accept(sock, (struct sockaddr *)&remote, &t)) == -1) {

                fprintf(stderr, "Error Accept\n");
                return EXIT_FAILURE;
            }
        }
        fprintf(stdout, "Verbindung hergestellt!\n");

        if (s3A == 0){
            s3A = 1;
            if ((sock3 = accept(sock, (struct sockaddr *)&remote, &t)) == -1) {

                fprintf(stderr, "Error Accept\n");
                return EXIT_FAILURE;
            }
        }
        fprintf(stdout, "Verbindung hergestellt!\n");
        fprintf(stdout, "\nSTART\n");
        done  = 0;
        while (!done){
            //Server sendet Start\n
            if (send(sock2, START, 6, 0) < 0) {
                fprintf(stderr, "Error send\n");
                return EXIT_FAILURE;
            }
            if (send(sock3, START, 6, 0) < 0) {
                fprintf(stderr, "Error send\n");
                return EXIT_FAILURE;
            }
            //Server bekommt Eingaben der Clienten
            n = recv(sock2, str, 100, 0);
            i = recv(sock2, str2, 100, 0);
            if (n <= 0 || i <= 0) {
                if (n < 0 || i < 0){
                    fprintf(stderr, "Error recv");
                }
                done = 1;
           }
           //Server berrechnet das Ergebnis
           answer = p1vsp2(str, str2);
           //Server sendet das Ergebnis
           if(answer == 0){
               send(sock2, "UNENTSCHIEDEN\n", 14, 0);
               send(sock3, "UNENTSCHIEDEN\n", 14, 0);
           }
           else if(answer == 1){
               send(sock2, "GEWONNEN\n", 9, 0);
               send(sock3, "VERLOREN\n", 9, 0);
           }
           else{
               send(sock2, "VERLOREN\n", 9, 0);
               send(sock3, "GEWONNEN\n", 9, 0);
           }
       }

    }

    return EXIT_SUCCESS;
}
