#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "_getline.h"

/**
 * _getline- get a line from a file descriptor
 * @fd: the file in question
 *
 * Return: null-terminated string that does not include newline
 */

char *_getline(const int fd)
{
	static ReadNode *head;
	ReadNode *node = load_node(fd, &head);

	if (fd == -1)
	{
		free_list(&head);
		return (NULL);
	}
	if (node->current == NULL)
	{
		node->current = node->buffer;
	}
	int bytes_read = read(fd, node->buffer, READ_SIZE);

	if (bytes_read < 0)
	{
		return (NULL);
	}
	node->nextLine = next_line_ptr(node->current);
	size_t length = (node->nextLine - node->current);
	char *char_buffer = strndup(node->current, length);

	if (char_buffer == NULL)
	{
		return (NULL);
	}
	node->current = node->nextLine + 1;
	return (char_buffer);
}

/**
 * load_node- loads a node
 * @fd: the file we're trying to work with
 * @head: the head of the linked list
 *
 * Return: the node with the data about the file
 */

ReadNode *load_node(int fd, ReadNode **head)
{
	ReadNode *current = *head;

	while (current != NULL)
	{
		if (current->fd == fd)
		{
			return (current);
		}
		current = current->next;
	}
	ReadNode *newNode = malloc(sizeof(ReadNode));

	if (newNode == NULL)
	{
		return (NULL);
	}
	newNode->fd = fd;
	newNode->current = NULL;
	newNode->nextLine = NULL;
	newNode->next = NULL;

	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newNode;
	}
	return (newNode);
}

/**
 * next_line_ptr- finds the pointer to the next newline
 * @line: the string in question
 *
 * Return: the pointer found
 */

char *next_line_ptr(char *line)
{
	while (*line != '\n' && *line != '\0')
	{
		line++;
	}
	if (*line == '\n' || *line == '\0')
	{
		return (line);
	}
	return (NULL);
}

/**
 * free_list- frees a linked list
 * @head: the head of the list in question
 *
 * Return: no return
 */

void free_list(ReadNode **head)
{
	ReadNode *current = *head;
	ReadNode *next_node;

	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	*head = NULL;
}
