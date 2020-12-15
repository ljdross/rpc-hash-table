#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXDATASIZE 128

int main(int argc, char **argv) {
    int sockfd, numbytes = 1;
    u_int8_t buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;

    if (argc != 3) {
        fprintf(stderr, "client usage: client hostname portnumber\n");
        exit(1);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
        fprintf(stderr, "client getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket() failed");
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect() failed");
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL) {
        fprintf(stderr, "client: could not connect to any\n");
        return 2;
    } else {
        fprintf(stderr, "client: connected\n");
    }

    while (numbytes > 0) {
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
            perror("client: recv() failed");
            exit(2);
        }
        fwrite(buf, sizeof(u_int8_t), numbytes, stdout);
    }

    close(sockfd);

    return 0;
}
