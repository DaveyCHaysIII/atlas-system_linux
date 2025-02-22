#include "sockets.h"

/**
 * create_ssocket - creates and initializes a server socket
 * @port: the port to use
 * @backlog: the backlog
 *
 * This function handles the socket(), bind() and listen()
 * elements of a server socket
 *
 * Return: the socket FD
 */

int create_ssocket(int port, int backlog)
{
	int sock_fd
	struct sockaddr_in serv_addr;
	ssize_t addr_len;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("serv_socket");
		exit(EXIT_FAILURE);
	}

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	addr_len = sizeof(serv_addr);

	bind_fd = bind(sock_fd, (struct sockaddr *)&serv_addr, addr_len);
	if (bind_fd < 0)
	{
		perror("serv_bind");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	if (listen(sock_fd, backlog) < 0)
	{
		perror("serv_listen");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", port);
	return (sock_fd);
}

/**
 * create_csocket - creates and initializes a client socket
 * @ip: the IP address
 * @port: the port to use
 *
 * This function handles the socket() initialization for
 * a client socket
 *
 * Return: the socket FD
 */

int create_csocket(const char *ip, int port)
{
	int sock_fd;
	struct sockaddr_in serv_addr;
	ssize_t addr_len;

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &serv_addr.sin_addr);

	addr_len = sizeof(serv_addr);

	if (connect(sock_fd, (stuct sockaddr *)&serv_addr, addr_len) < 0)
	{
		perror(client_connect);
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	return (sock_fd);
}

/**
 *
 */



/**
 *
 */


/**
 *
 */
