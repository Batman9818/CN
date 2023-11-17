#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/types.h>
#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    while (1) {
        printf("Client: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        sendto(client_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	bzero(buffer,sizeof(buffer));
        recvfrom(client_fd, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL);
        printf("Server: %s", buffer);
    }
    close(client_fd);
    return 0;
}
