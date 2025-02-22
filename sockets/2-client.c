#include "sockets.h"

/**
 * main - entry point
 * @argc: number of args
 * @argv: arg vector
 * Return: 0
 */

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Usage: %s <host> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *host = argv[1];
	unsigned short port = atoi(argv[2]);
	int sock_fd;
	struct sockaddr_in address;
	struct hostent *server = gethostbyname(host);

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = *(in_addr_t *)server->h_addr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	if (connect(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}

	printf("Connected to %s:%d\n", host, port);
	return (0);
}
