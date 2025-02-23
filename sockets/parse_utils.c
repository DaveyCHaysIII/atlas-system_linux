#include "sockets.h"

#define MAX_QUERIES 10
#define MAX_KEYVAL_LEN 16

/**
 * parse_req - parse an HTTP request
 * @recvbuf: raw req string
 * @req: pointer to data structure to hold parsed data
 *
 * Return: 0 on success
 */

int parse_req(char *recvbuf, httpreq *req)
{
	char *line_end, *line, *method, *path, *version, *query;

	line_end = strchr(recvbuf, '\r');
	if (!line_end)
		return (-1);
	*line_end = '\0';
	line = recvbuf;

	method = strtok(line, " ");
	path = strtok(NULL, " ");
	version = strtok(NULL, " ");
	strcpy(req->method, method);
	strcpy(req->version, version);

	query = strchr(path, '?');
	if (query)
	{
		*query = '\0';
		strcpy(req->path, path);
		strcpy(req->query, query + 1);
		parse_queries(req);
	}
	else
	{
		strcpy(req->path, path);
		req->query[0] = '\0';
	}
	/*parse_headers(req);*/
	return (0);
}

/**
 * parse_queries - parse just the queries
 * @req: the data structure to hold the queries
 *
 * Return: no return
 */

void parse_queries(httpreq *req)
{
	char *pair, *key, *value;
	int i = 0;

	memset(req->qkeys, 0, sizeof(req->qkeys));
	memset(req->qvals, 0, sizeof(req->qvals));
	pair = strtok(req->query, "&");
	while (pair && MAX_QUERIES)
	{
		key = pair;
		value = strchr(key, '=');

		if (value)
		{
			*value = '\0';
			value++;
		}

		if (key)
			strncpy(req->qkeys[i], key, MAX_KEYVAL_LEN - 1);
		if (value)
			strncpy(req->qvals[i], value, MAX_KEYVAL_LEN - 1);
		i++;
		pair = strtok(NULL, "&");
	}
}

/**
 * parse_headers - parses the HTTP headers
 * @req: data structure to hold the HTTP request
 *
 * Return: no return
 */

void parse_headers(httpreq *req)
{
	(void)req;

}

/**
 * parse_body - parses the HTTP body
 * @req: data structure to hold the http request
 *
 * Return: no return
 */

void parse_body(httpreq *req)
{
	(void)req;
}
