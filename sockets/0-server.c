#include "sockets.h"

/**
 * main - primary C function
 *
 * Return: return 0
 */
int main(void)
{
	int sock_fd, bind_fd;
	struct sockaddr_in serv_addr;

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(12345);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

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
