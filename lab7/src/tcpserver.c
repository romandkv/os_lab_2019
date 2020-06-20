#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr

int main(int argc, char **argv) {
  const size_t kSize = sizeof(struct sockaddr_in);


    if (argc != 3) {
        printf("USAGE: ./%s [serv_port] [buffsize]", argv[0]);
        return 0;
    }

    int serv_port = atoi(argv[1]);
    int buffsize = atoi(argv[2]);
  int lfd, cfd;
  int nread;
  char buf[buffsize];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  memset(&servaddr, 0, kSize);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  /*
  The htonl() function converts the 
  unsigned integer hostlong from host byte order to network byte order.
  */
  servaddr.sin_port = htons(serv_port);

  if (bind(lfd, (SADDR *)&servaddr, kSize) < 0) {
      /*
        bind - bind a name to a socket
        (int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
      */
    perror("bind");
    exit(1);
  }

  if (listen(lfd, 5) < 0) {
      /*
       listen - listen for connections on a socket
       int listen(int sockfd, int backlog);
      */
    perror("listen");
    exit(1);
  }

  while (1) {
    unsigned int clilen = kSize;

    if ((cfd = accept(lfd, (SADDR *)&cliaddr, &clilen)) < 0) {
        /*
         accept, accept4 - accept a connection on a socket
       int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        */
      perror("accept");
      exit(1);
    }
    printf("connection established\n");

    while ((nread = read(cfd, buf, buffsize)) > 0) {
      write(1, &buf, nread);
    }

    if (nread == -1) {
      perror("read");
      exit(1);
    }
    close(cfd);
  }
}
