#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char buf[10];
    int bread, fdes;
    printf("1\n");
    int i =mkfifo("Com.fifo", 0664);
    if (i!=0){
        printf("Error mkfifo\n");
        return EXIT_FAILURE;
    }

    printf("2\n");
    fdes = open("Com.fifo", O_RDONLY | O_CREAT);
    printf("2.5\n");
    if (fdes == -1){
        return EXIT_FAILURE;
    }
    printf("3");


    while (1){
        bread = read(fdes, buf,  10);
        printf("4");
        if (bread !=0 ){
            write(1,buf,10);
                printf("5");
        }
}
    return EXIT_SUCCESS;
}
