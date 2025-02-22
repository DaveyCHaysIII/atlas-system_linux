#include "sockets.h"

#define MAX_BUFF 1024

/**
 * main - entry point
 *
 * Return: 0
 */

int main(void)
{
	int sock_fd, bind_fd, client_fd, port = 12345;
	struct sockaddr_in serv_addr;
	socklen_t addr_len = sizeof(serv_addr);
	char recvbuf[MAX_BUFF];
	ssize_t bytes_recieved;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind_fd = bind(sock_fd, (struct sockaddr *)&serv_addr, addr_len);
	if (bind_fd < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if (listen(sock_fd, 10) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", port);
	client_fd = accept(sock_fd, (struct sockaddr *)&serv_addr, &addr_len);
	if (client_fd < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("Client connected: %s\n", inet_ntoa(serv_addr.sin_addr));
	bytes_recieved = recv(client_fd, recvbuf, sizeof(recvbuf) - 1, 0);
	recvbuf[bytes_recieved] = '\0';
	printf("Message received: \"%s\"\n", recvbuf);
	return (0);
}


