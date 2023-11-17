#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
int main()
{
    struct sockaddr_in sa;
    struct sockaddr_in cli;
    int sockfd, conntfd;
    socklen_t len;
    int ch = 0;
    char str[100];
    time_t tick;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&sa, 0, sizeof(sa));
    sa.sin_port = htons(5600);
    sa.sin_addr.s_addr = htonl(0);
    bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    listen(sockfd, 50);
    for (;;)
    {
        len = sizeof(ch);
        conntfd = accept(sockfd, (struct sockaddr *)&cli, &len);
        printf("Accepted");
        tick = time(NULL);
        snprintf(str, sizeof(str), "%s", ctime(&tick));
        printf("\n%s", str);
        write(conntfd, str, strlen(str));
    }
    return 0;
}
