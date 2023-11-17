#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h> 
int main()
{
    struct sockaddr_in sa;
    int n, sockfd;
    char buff[100];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(5600);
    connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    n = fread(buff, sizeof(char), sizeof(buff), stdin));
    printf("\nMessage Read %s", buff);
    return 0;
}
