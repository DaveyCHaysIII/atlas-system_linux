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
	int sock_fd, bind_fd, optval = 1;
	struct sockaddr_in serv_addr;
	ssize_t addr_len, op_len;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("serv_socket");
		exit(EXIT_FAILURE);
	}
	op_len = sizeof(optval);
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, op_len) < 0)
	{
		perror("serv_sockopt");
		close(sock_fd);
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
 * a client socket (**unused in this project**)
 *
 * Return: the socket FD
 */

int create_csocket(const char *ip, int port)
{
	int sock_fd;
	struct sockaddr_in serv_addr;
	ssize_t addr_len;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("client_socket");
		exit(EXIT_FAILURE);
	}

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &serv_addr.sin_addr);

	addr_len = sizeof(serv_addr);

	if (connect(sock_fd, (struct sockaddr *)&serv_addr, addr_len) < 0)
	{
		perror("client_connect");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	return (sock_fd);
}

/**
 * handle_accept - handles the accept function
 * @sock_fd: the socket fd for the server
 * @addr: the sockaddr_in struct for the client
 * @addr_len: the length of the addr struct
 *
 * Return: the client fd (exit failure on err)
 */

int handle_accept(int sock_fd, struct sockaddr_in *addr, socklen_t *addr_len)
{
	int client_fd;

	client_fd = accept(sock_fd,
		(struct sockaddr *)addr,
		addr_len);
	if (client_fd < 0)
	{
		perror("accept");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	printf("Client connected: %s\n", inet_ntoa(addr->sin_addr));
	return (client_fd);
}

