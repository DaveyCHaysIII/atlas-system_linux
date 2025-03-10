#ifndef SERVER_H
#define SERVER_H

#define MAX_BUFF 1024
#define MAX_KV 10
#define MAX_KV_CHARS 64

#define MAX_TODOS 10

#define RESP_200 "200 OK"
#define RESP_201 "201 Created"
#define RESP_204 "204 No Content"
#define RESP_404 "404 Not Found"
#define RESP_411 "411 Length Required"
#define RESP_422 "422 Unprocessable Entity"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>


/**
 * struct todo - the struct for making a new todo
 * @id: the uuid of the todo
 * @title: the title of the todo
 * @description: the description of the todo
 *
 * This data structure should make handling
 * and creating new todos much simpler
 *
 */

typedef struct todo
{
	int in_use;
	int id;
	char title[48];
	char description[64];
	char resp_string[1024];
} todo;

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
	char version[16];
	char response_code[32];
	char qkeys[MAX_KV][MAX_KV_CHARS];
	char qvals[MAX_KV][MAX_KV_CHARS];
	char hkeys[MAX_KV][MAX_KV_CHARS];
	char hvals[MAX_KV][MAX_KV_CHARS];
	char bkeys[MAX_KV][MAX_KV_CHARS];
	char bvals[MAX_KV][MAX_KV_CHARS];
	int current_id;
	todo todos[MAX_TODOS];
} httpreq;


void route_handler(httpreq *req, int client_fd);
void make_todo(httpreq *req);

/* socket_utils.c */
int create_ssocket(int port, int backlog);
int create_csocket(const char *ip, int port);
int handle_accept(int sock_fd, struct sockaddr_in *addr, socklen_t *addr_len);

/* parse_utils.c */
int parse_req(char *recvbuf, httpreq *req);
void parse_queries(httpreq *req);
void parse_headers(httpreq *req, char *recvbuf);
void parse_body(httpreq *req, char *recvbuf);
int parse_resp_code (httpreq *req);

/* print_utils.c */
void print_req(httpreq *req);
void print_queries(httpreq *req);
void print_headers(httpreq *req);
void print_body(httpreq *req);

#endif
