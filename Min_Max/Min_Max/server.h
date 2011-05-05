#ifndef _STATE_FNS
#define _STATE_FNS

int init_socket();
int state_query(int sockfd, const char * varname, char * output);
int state_update(int sockfd, const char * varname, const char * value);
void close_socket(int sockfd);

#endif