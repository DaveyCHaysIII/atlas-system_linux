#ifndef SERVER_H
#define SERVER_H

#define MAX_BUFF 1024

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * httpreq - struct to hold parsed HTTP data
 * @method: HTTP method (GET, POST, etc)
 * @path: the path its looking for
 * @version: the HTTP version
 * @host: the host (localhost, etc)
 * @user_agent: I don't know this one
 * @accept: the accept
 */

typedef struct {
	char method[8];
	char path[MAX_BUFF];
	char version[16];
	char host[MAX_BUFF];
	char user_agent[MAX_BUFF];
	char accept[MAX_BUFF];
} httpreq;

int create_ssocket(int port, int backlog);
int create_csocket(const char *ip, int port);
int handle_accept(int sock_fd, struct sockaddr_in *addr, socklen_t *addr_len);
int parse_req(const char *recvbuf, httpreq *req);
void print_req(httpreq *req);
#endif
