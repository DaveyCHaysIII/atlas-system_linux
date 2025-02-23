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
 * struct httpreq - struct to hold parsed HTTP data
 * @method: HTTP method (GET, POST, etc)
 * @path: the path its looking for
 * @query: the query string
 * @qkeys: the 2D array of query keys
 * @qvals: the 2D array of query values
 * @version: the HTTP version
 * @host: the host (localhost, etc)
 * @user_agent: I don't know this one
 * @accept: the accept
 *
 * This data structure holds all the parsed data from the HTTP request
 *
 */

typedef struct httpreq
{
	char method[8];
	char path[MAX_BUFF];
	char query[MAX_BUFF];
	char qkeys[10][16];
	char qvals[10][16];
	char version[16];
	char host[MAX_BUFF];
	char user_agent[MAX_BUFF];
	char accept[MAX_BUFF];
} httpreq;

/* socket_utils.c */
int create_ssocket(int port, int backlog);
int create_csocket(const char *ip, int port);
int handle_accept(int sock_fd, struct sockaddr_in *addr, socklen_t *addr_len);

/* parse_utils.c */
int parse_req(char *recvbuf, httpreq *req);
void parse_queries(httpreq *req);
void parse_headers(httpreq *req);
void parse_body(httpreq *req);

/* print_utils.c */
void print_req(httpreq *req);
void print_queries(httpreq *req);
void print_headers(httpreq *req);
void print_body(httpreq *req);

#endif
