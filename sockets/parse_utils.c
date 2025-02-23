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
	char *line_end = strchr(recvbuf, '\r');
	if (!line_end) return (-1);

	*line_end = '\0';
	char *line = recvbuf;

	char *method = strtok(line, " ");
	char *path = strtok(NULL, " ");
	char *version = strtok (NULL, " ");

	strcpy(req->method, method);
	strcpy(req->version, version);

	char *query = strchr(path, '?');
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
	char *header_start = line_end + 2;
	while (*header_start != '\r')
	{
		char *key = strtok(header_start, ": ");
		char *value = strtok(NULL, "\r");

		if (strcmp(key, "Host") == 0) strcpy(req->host, value);
		if (strcmp(key, "User-Agent") == 0)
			strcpy(req->user_agent, value);
		if (strcmp(key, "Accept") == 0) strcpy(req->accept, value);
		header_start += strlen(key) + strlen(value);
	}
	return (0);
}

/**
 * parse_queries - parse just the queries
 * @req - the data structure to hold the queries
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
		key = strtok(pair, "=");
		value = strtok(NULL, "=");

		if (key) strncpy(req->qkeys[i], key, MAX_KEYVAL_LEN - 1);
		if (value) strncpy(req->qvals[i], value, MAX_KEYVAL_LEN -1);

		i++;
		pair = strtok(NULL, "&");
	}
}
