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
	char *msg = "HTTP/1.1 200 OK\r\n";
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
		print_body(&req);
		fflush(stdout);
		if (send(client_fd, msg, strlen(msg), 0) < 0)
			perror("send");
		close(client_fd);
	}
	close(sock_fd);
}

