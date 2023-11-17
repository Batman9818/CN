#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/types.h>
#define PORT 2345
#define MAX_BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE];
    sock = socket(AF_INET, SOCK_STREAM, 0) ;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while (1) {
     	printf("Client: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
	bzero(buffer,sizeof(buffer));
        recv(sock, buffer, MAX_BUFFER_SIZE, 0);
        printf("Server: %s", buffer);
    }
    close(sock);
    return 0;
}
