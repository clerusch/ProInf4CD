#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    File * stream = fopen("Com",r);

    if (stream){
    
    }    
    else{
        mkfifo("Com", 0400);
        return EXIT_SUCESS;
    }
