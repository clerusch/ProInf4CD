/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <arpa/inet.h>
int p1vsp2(char* p1, char* p2){
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

int main(){
  int welcomeSocket, newSocket, player2;
  char buffer[1024], buffer2[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("localhost");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  player2 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  /*---- Send message to the socket of the incoming connection ----*/
  int answer;
  while(1){
      recv(newSocket, buffer2, 1024, 0);
      recv(player2, buffer, 1024, 0);
      answer = p1vsp2(buffer, buffer2);
      if(answer == 0){
          send(newSocket, "UNENTSCHIEDEN\n", 1024, 0);
          send(player2, "UNENTSCHIEDEN\n", 1024, 0);
      }
      if(answer == 1){
          send(newSocket, "GEWONNEN\n", 1024, 0);
          send(player2, "VERLOREN\n", 1024, 0);
      }
      else{
          send(newSocket, "VERLOREN\n", 1024, 0);
          send(player2, "GEWONNEN\n", 1024, 0);
      }
  }
  return 0;
}
