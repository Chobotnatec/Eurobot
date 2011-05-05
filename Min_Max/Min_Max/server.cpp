#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
  perror(msg);
  exit(1);
}

int state_query(int sockfd, const char * varname, char * output) {
  int n;
  char * buffer;

  n = write(sockfd, varname, strlen(varname));
  if(n < 0)
    error("ERROR writing to socket");

  buffer = (char *)malloc(sizeof(char)*256);
  n = read(sockfd, buffer, 255);
  if(n < 0)
    error("ERROR reading from socket");

  if(strcmp(buffer, "_na\n") == 0)
    return 1;

  strcpy(output, buffer);
  return 0;
}

int state_update(int sockfd, const char * varname, const char * value) {
  int n;
  char * buffer;
  char cmd[256];
  snprintf(cmd, sizeof(cmd), "%s %s", varname, value);

  n = write(sockfd, cmd, strlen(cmd));
  if(n < 0)
    error("ERROR writing to socket");

  buffer = (char *)malloc(sizeof(char)*256);
  n = read(sockfd, buffer, 255);
  if(n < 0)
    error("ERROR reading from socket");

  if(strcmp(buffer, "ok\n") == 0)
    return 0;

  return 1;

}

int init_socket() {
  // TODO (minor): configurable port/host
  int sockfd;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  int portno = 12300;
  const char * host = "localhost";

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
  server = gethostbyname(host);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(1);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
    (char *)&serv_addr.sin_addr.s_addr,
    server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  return sockfd;
}

void close_socket(int sockfd) {
  close(sockfd);
}