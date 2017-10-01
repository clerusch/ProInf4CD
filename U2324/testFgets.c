#include <stdio.h>

#define buffSize 100

int main(){
    char buff[buffSize];
    printf("Bitte geben Sie Ihren Namen ein : ");
    fgets(buff, buffSize, stdin);
    printf("Hallo %s",buff);
    while (printf("Client> "), fgets(buff, buffSize, stdin), !feof(stdin)){
        printf("buff: %s", buff);
    }
}
