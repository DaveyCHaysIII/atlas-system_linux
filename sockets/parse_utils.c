#include "sockets.h"

#define MAX_ENTRIES 10
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

	memset(req->method, 0, sizeof(req->method));
	memset(req->path, 0, sizeof(req->path));
	memset(req->query, 0, sizeof(req->query));
	memset(req->version, 0, sizeof(req->version));
	memset(req->response_code, 0, sizeof(req->response_code));
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
	parse_body(req, orig_req);
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
	char *temp, *pair, *key, *value;
	int i = 0;

	temp = malloc(strlen(req->query) + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	strcpy(temp, req->query);
	memset(req->qkeys, 0, sizeof(req->qkeys));
	memset(req->qvals, 0, sizeof(req->qvals));
	pair = strtok(temp, "&");
	while (pair && MAX_ENTRIES)
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
	free(temp);
}

/**
 * parse_headers - parses the HTTP headers
 * @req: data structure to hold the HTTP request
 * @recvbuf: the original request
 * Return: no return
 */

void parse_headers(httpreq *req, char *recvbuf)
{
	char *temp, *line, *next_line, *key, *value;
	int i = 0;

	memset(req->hkeys, 0, sizeof(req->hkeys));
	memset(req->hvals, 0, sizeof(req->hvals));
	temp = malloc(strlen(recvbuf) + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	strcpy(temp, recvbuf);
	line = strstr(temp, "\r\n");
	if (!line)
	{
		free(temp);
		exit(EXIT_FAILURE);
	}
	line += 2;
	while (line && *line && i < MAX_ENTRIES)
	{
		if (strncmp(line, "\r\n", 2) == 0)
			break;
		next_line = strstr(line, "\r\n");
		if (next_line)
		{
			*next_line = '\0';
			next_line += 2;
		}
		key = strtok(line, ":");
		value = strtok(NULL, "\r\n");
		if (key && value)
		{
			strcpy(req->hkeys[i], key);
			strcpy(req->hvals[i], value + 1);
			i++;
		}
		line = next_line;
	}
	free(temp);
}

/**
 * parse_body - parses the HTTP body
 * @req: data structure to hold the http request
 * @recvbuf: the original request
 *
 * Return: no return
 */

void parse_body(httpreq *req, char *recvbuf)
{
	char *temp, *line, *value, *key;
	int i = 0;

	memset(req->bkeys, 0, sizeof(req->bkeys));
	memset(req->bvals, 0, sizeof(req->bvals));
	temp = malloc(strlen(recvbuf) + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	strcpy(temp, recvbuf);
	line = strstr(temp, "\r\n\r\n");
	if (!line)
	{
		free(temp);
		exit(EXIT_FAILURE);
	}
	line += 4;
	key = strtok(line, "&");
	while (key && i < MAX_ENTRIES)
	{
		value = strchr(key, '=');

		if (value)
		{
			*value = '\0';
			value++;
			strcpy(req->bkeys[i], key);
			strcpy(req->bvals[i], value);
			i++;
		}
		key = strtok(NULL, "&");
	}
	free(temp);
}
