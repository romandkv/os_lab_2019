#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {

    if (argc != 4) {
    printf("Too few arguments \n")
    exit(1);
  }
    int buffsize = atoi(argv[3]);
  int fd;
  int nread;
  char buf[buffsize];
  struct sockaddr_in servaddr;
  /*
  struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
  */


  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      //(int domain, int type, int protocol) : file descriptor
      // AF_INET      IPv4 Internet protocols
      // SOCK_STREAM     Provides sequenced, reliable, two-way, connection-
      //      based byte streams.  An out-of-band data transmission
      //      mechanism may be supported. (TCP)
    perror("socket creating");
    exit(1);
  }

  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;

  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
      /*
             inet_pton - convert IPv4 and IPv6 addresses from text to binary form
             (int af, const char *src, void *dst)
             af address family
      */
    perror("bad address");
    exit(1);
  }

  servaddr.sin_port = htons(atoi(argv[2]));
  /*
  The htons() function converts 
  the unsigned short integer hostshort
  from host byte order to network byte order.
  */

  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
      /*
      connect - initiate a connection on a socket
      (
            int sockfd, 
            const struct sockaddr *addr,
            socklen_t addrlen
        );
      */
    perror("connect");
    exit(1);
  }

  write(1, "Input message to send\n", 22);
  while ((nread = read(0, buf, buffsize)) > 0) {
    if (write(fd, buf, nread) < 0) {
      perror("write");
      exit(1);
    }
  }

  close(fd);
  exit(0);
}
