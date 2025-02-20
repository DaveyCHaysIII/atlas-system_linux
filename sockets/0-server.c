#include "sockets.h"

/**
 * main - primary C function
 *
 * Return: return 0
 */
int main()
{
	int sock_fd, bind_fd;
	uint32_t port;
	struct sockaddr_in serv_addr;

	port = 12345;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htonl(12345);

	bind_fd = bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (bind_fd < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", port);
	while (1)
	{
		listen(sock_fd, 10);
	}
	return (0);
}
