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
	memset(req.todos, 0, sizeof(req.todos));
	req.current_id = 0;
	while (1)
	{
		client_fd = handle_accept(sock_fd, &client_addr, &addr_len);
		bytes_recv = recv(client_fd, recvbuf, sizeof(recvbuf) - 1, 0);
		recvbuf[bytes_recv] = '\0';
		parse_req(recvbuf, &req);
		route_handler(&req, client_fd);
		fflush(stdout);
		close(client_fd);
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

void route_handler(httpreq *req, int client_fd)
{
	int resp;
	size_t cont_len;
	char resp_buf[5120];

	resp = parse_resp_code(req);
	if (resp == 201)
	{
		printf("Route 201\n");
		make_todo(req);
		cont_len = strlen(req->todos[req->current_id].resp_string);
		sprintf(resp_buf, "HTTP/1.1 201 Created\r\nContent-Length: %zu\r\nContent-Type: application/json\r\n\r\n%s\r\n",cont_len,req->todos[req->current_id].resp_string);
		send(client_fd, resp_buf, strlen(resp_buf), 0);
		req->current_id++;
	}
	else
		send(client_fd, req->response_code, strlen(req->response_code), 0);
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
	if (!((strcmp(req->method, "GET") == 0 || strcmp(req->method, "POST") == 0) && strcmp(req->path, "/todos") == 0))
	{
		strcpy(req->response_code, "HTTP/1.1 404 Not Found\r\n");
		return (404);
	}
	if (strcmp(req->method, "POST") == 0)
	{
		has_content_length = 0;
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
			strcpy(req->response_code, "HTTP/1.1 411 Length Required\r\n");
			return (411);
		}
		has_title = 0;
		has_description = 0;
		for (i = 0; i < MAX_KV; i++)
		{
			if (strcmp(req->bkeys[i], "title") == 0)
				has_title = 1;
			if (strcmp(req->bkeys[i], "description") == 0)
				has_description = 1;
		}
		if (has_title == 0 || has_description == 0)
		{
			strcpy(req->response_code, "HTTP/1.1 422 Unprocessable Entity\r\n");
			return (422);
		}
		strcpy(req->response_code, "HTTP/1.1 201 Created\r\n");
		return (201);
	}
	strcpy(req->response_code, "HTTP/1.1 200 OK\r\n");
	return (200);
}

/**
 * make_todo - makes the todo
 * @req: the data structure holding the request
 *
 * Return: no return
 */

void make_todo(httpreq *req)
{
	int c_id;
	char buffer[MAX_BUFF];

	c_id = req->current_id;
	req->todos[c_id].id = c_id;
	strcpy(req->todos[c_id].title, req->bvals[0]);
	strcpy(req->todos[c_id].description, req->bvals[1]);
	sprintf(buffer,
		"{\"id\":%d,\"title\":\"%s\",\"description\":\"%s\"}",
		req->todos[c_id].id,
		req->todos[c_id].title,
		req->todos[c_id].description);
	strcpy(req->todos[c_id].resp_string, buffer);
	printf("Todo created: %s\n", req->todos[c_id].resp_string);
}
