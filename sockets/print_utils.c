#include "sockets.h"

#define MAX_ENTRIES 10


/**
 * print_req - print an HTTP request
 * @req: the data structure to pull from
 *
 * Return: no return
 */

void print_req(httpreq *req)
{
	printf("Method: %s\nPath: %s\nVersion: %s\n",
			req->method,
			req->path,
			req->version);
}


/**
 * print_queries - print an HTTP request
 * @req: the data structure to pull from
 *
 * Return: no return
 */

void print_queries(httpreq *req)
{
	int i = 0;

	printf("Path: %s\n", req->path);
	while (i < MAX_ENTRIES && req->qkeys[i][0] != '\0')
	{
		printf("Query: \"%s\" -> \"%s\"\n", req->qkeys[i], req->qvals[i]);
		i++;
	}
}


/**
 * print_headers - print an HTTP request
 * @req: the data structure to pull from
 *
 * Return: no return
 */

void print_headers(httpreq *req)
{
	int i = 0;

	printf("Path: %s\n", req->path);
	while (i < MAX_ENTRIES && req->hkeys[i][0] != '\0')
	{
		printf("Header: \"%s\" -> \"%s\"\n", req->hkeys[i], req->hvals[i]);
		i++;
	}
}


/**
 * print_body - print an HTTP request
 * @req: the data structure to pull from
 *
 * Return: no return
 */

void print_body(httpreq *req)
{
	(void)req;
}
