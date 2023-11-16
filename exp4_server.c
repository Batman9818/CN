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
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up sockaddr_in structure for server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to localhost:8080
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
    	bzero(buffer,sizeof(buffer));
        // Receive data from the client
        if (recvfrom(server_fd, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len) == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        printf("Client: %s", buffer);
	bzero(buffer,sizeof(buffer));
        // Send data to the client
        printf("Server: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_len);
    }

    close(server_fd);
    return 0;
}
