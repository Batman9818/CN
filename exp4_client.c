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

    // Create socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set up sockaddr_in structure for server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Send data to the server
        printf("Client: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        sendto(client_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	bzero(buffer,sizeof(buffer));
        // Receive data from the server
        if (recvfrom(client_fd, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL) == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        printf("Server: %s", buffer);
    }

    close(client_fd);
    return 0;
}
