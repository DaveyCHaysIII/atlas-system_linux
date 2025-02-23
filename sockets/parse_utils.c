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
	char *orig_req, *line_end, *line, *method, *path, *version, *query;

	orig_req = malloc(strlen(recvbuf) + 1);
	strcpy(orig_req, recvbuf);
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
	parse_headers(req, orig_req);
	free(orig_req);
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
 * @recvbuf: the original request
 * Return: no return
 */

void parse_headers(httpreq *req, char *recvbuf)
{
	char *temp, *header_start, *key, *value;
	int i = 0;

	memset(req->hkeys, 0, sizeof(req->hkeys));
	memset(req->hvals, 0, sizeof(req->hvals));
	temp = malloc(strlen(recvbuf) + 1);
	if (!temp)
		exit(EXIT_FAILURE);

	strcpy(temp, recvbuf);
	header_start = strstr(temp, "\r\n");
	if (!header_start)
	{
		free(temp);
		exit(EXIT_FAILURE);
	}
	header_start += 2;

	while (*header_start)
	{
		if (strncmp(header_start, "\r\n", 2) == 0)
			break;

		key = strtok(header_start, ":");
		value = strtok(NULL, "\r\n");

		if (key && value)
		{
			strcpy(req->hkeys[i], key);
			strcpy(req->hvals[i], value + 1);
			i++;
		}
		header_start = strchr(header_start, '\n');
		if (header_start)
			header_start++;
		else
			break;
	}

	free(temp);
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
