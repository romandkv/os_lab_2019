#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("USAGE: ./%s [buffsize] [serv_port]", argv[0]);
        return 0;
    }

    int serv_port = atoi(argv[1]);
    int buffsize = atoi(argv[2]);
  int sockfd, n;
  char mesg[buffsize], ipadr[16];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  memset(&servaddr, 0, SLEN);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(serv_port);

  if (bind(sockfd, (SADDR *)&servaddr, SLEN) < 0) {
    perror("bind problem");
    exit(1);
  }
  printf("SERVER starts...\n");

  while (1) {
    unsigned int len = SLEN;

    if ((n = recvfrom(sockfd, mesg, buffsize, 0, (SADDR *)&cliaddr, &len)) < 0) {
      perror("recvfrom");
      exit(1);
    }
    mesg[n] = 0;

    printf("REQUEST %s      FROM %s : %d\n", mesg,
           inet_ntop(AF_INET, (void *)&cliaddr.sin_addr.s_addr, ipadr, 16),
           ntohs(cliaddr.sin_port));
           /*
                  inet_ntop - convert IPv4 and IPv6 addresses from binary to text form
       const char *inet_ntop(int af, const void *src,
                             char *dst, socklen_t size);

            
                The ntohs() function converts the
                unsigned short integer netshort from network byte order to host byte order.
           */

    if (sendto(sockfd, mesg, n, 0, (SADDR *)&cliaddr, len) < 0) {
      perror("sendto");
      exit(1);
    }
  }
}
