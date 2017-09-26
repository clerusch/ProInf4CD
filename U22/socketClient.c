#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

itn main (void){
    int s, len;
    socklen_t t;
    struct sockaddr_un remote;
    char buff[100];


    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "Error Socket erstellung\n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
