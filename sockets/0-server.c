#include "sockets.h"

/**
 * main - primary C function
 *
 * Return: return 0
 */
int main(void)
{
	int sock_fd, bind_fd;
	struct sockaddr_in serv_addr = {
		AF_INET,
		htons(12345),
		{
			htons(INADDR_ANY)
		},
		{0x00}
	};

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}


	bind_fd = bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (bind_fd < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	listen(sock_fd, 10);
	printf("Server listening on port 12345\n");

	while (1)
	{

	}
	return (0);
}
