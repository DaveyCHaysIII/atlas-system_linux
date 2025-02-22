#include "sockets.h"


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


}


/**
 * print_headers - print an HTTP request
 * @req: the data structure to pull from
 *
 * Return: no return
 */

void print_headers(httpreq *req)
{

}


/**
 * print_body - print an HTTP request
 * @req: the data structure to pull from
 *
 * Return: no return
 */

void print_body(httpreq *req)
{

}
