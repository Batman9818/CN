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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE];
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Server listening on port %d\n", PORT);
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    while (1){
    	bzero(buffer,sizeof(buffer));
        recv(new_socket, buffer, MAX_BUFFER_SIZE, 0);
        printf("Client: %s", buffer);
	bzero(buffer,sizeof(buffer));
        printf("Server: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        send(new_socket, buffer, strlen(buffer), 0);
    }
    close(server_fd);
    return 0;
}
