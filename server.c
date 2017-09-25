#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){

    int i =mkfifo("Com.fifo", 0400);
            printf("i: %d", i);

//Überprüfen ob i != 0
/*    if (stream){
        printf("i: %d", i);
    }
    else{
        mkfifo("Com", 0400);

    }*/

    char buf[10];
    int bread;
    while(1){
        bread = ssize_t read(int Com,void *buf, size_t 10);
        if (bread !=0 ){
            write(1,buf,10);
        }
    }




    return EXIT_SUCCESS;
}
