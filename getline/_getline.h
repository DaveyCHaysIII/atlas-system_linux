#ifndef MAIN_H
#define MAIN_H

#define READ_SIZE 2047

/**
 * struct ReadNode - Structure for managing file reading state
 * @fd: File descriptor associated with the read operation
 * @buffer: Buffer used to store data read from the file
 * @current: Pointer to the current position in the buffer
 * @nextLine: Pointer to the start of the next line in the buffer
 * @next: Pointer to the next ReadNode in the linked list
 *
 * Description: This structure holds the state information for reading
 * data from a file. It includes the file descriptor, a buffer for data,
 * pointers for tracking positions within the buffer, and a link to the
 * next node in a linked list.
 */

typedef struct ReadNode
{
	int fd;
	char buffer[2048];
	char *current;
	char *nextLine;
	struct ReadNode *next;
} ReadNode;

ReadNode *load_node(int fd, ReadNode **head);
char *_getline(const int fd);
char *next_line_ptr(char *line);
void free_list(ReadNode **head);
char *char_buffer_init(ReadNode *node);
#endif
