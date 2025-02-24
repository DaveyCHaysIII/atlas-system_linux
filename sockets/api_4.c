#include "sockets.h"

#define PORT 8080
#define MAX_BUFF 1024

/**
 * main - entry point of API
 *
 * Return: 0
 */

int main(void)
{
	int sock_fd, client_fd;
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	char recvbuf[MAX_BUFF];
	ssize_t bytes_recv;
	httpreq req;

	sock_fd = create_ssocket(PORT, 10);

	while (1)
	{
		client_fd = handle_accept(sock_fd, &client_addr, &addr_len);
		bytes_recv = recv(client_fd, recvbuf, sizeof(recvbuf) - 1, 0);
		recvbuf[bytes_recv] = '\0';
		printf("Raw request: \"%s\"\n", recvbuf);
		memset(&req, 0x00, sizeof(req));
		parse_req(recvbuf, &req);
		route_handler(&req, client_fd);
		fflush(stdout);
	}
	close(sock_fd);
}

/**
 * route_handler - handles the routing for the server
 * @req: the data structure holding the http req data
 * @client_fd: the fd of the client
 *
 * Return: no return
 */

void route_handler(httpreq *req, client_fd)
{
	int resp;

	resp = parse_resp_code(&req);
	if (strcmp(req->method, "POST") && resp == 201)
	{
		//create todo

	}
	else if (resp == 200)
	{

	}
	else
	{

	}

	print_resp(*req, client_fd);
}

/**
 * parse_resp_code - validates input and determines response code
 * @req: the data structure holding the req data
 *
 * Return: response code
 */

int parse_resp_code(httpreq *req)
{
	int i, has_title, has_description, has_content_length;

	memset(req->response_code, 0, 32);
	if (!strcmp(req->method, "GET") || !strcmp(req->method, "POST") ||
		!strcmp(req->path, "/todos"))
	{
		strcpy(req->response_code, "404 Not Found");
		return (404);
	}
	if (strcmp(req->method, "POST"))
	{
		int has_content_length = 0;
		for (i = 0; i < MAX_KV; i++)
		{
			if (strcmp(req->hkeys[i], "Content-Length") == 0)
			{
				has_content_length = 1;
				break;
			}
		}
		if(!has_content_length)
		{
			strcpy(req->response_code, "411 Length Required");
			return (411);
		}
		has_title = 0;
		has_description = 0;
		for (i = 0; i < MAX_KV; i++)
		{
			if (!strcmp(req->bkeys[i], "Title"))
				has_title = 1;
			if (!strcmp(req->bkeys[i], "Description"))
				has_description = 1;
		}
		if (!has_title || !has_description)
		{
			strcpy(req->response_code, "422 Unprocessable Entity");
			return (422);
		}
		strcpy(req->response_code, "201 Created");
		return (201);
	}
	strcpy(req->response_code, "200 OK");
	return (200);
}
