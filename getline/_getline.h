#ifndef MAIN_H
#define MAIN_H

#define READ_SIZE 512

typedef struct ReadNode
{
	int fd;
	char buffer[1024];
	char *current;
	char *nextLine;
	struct ReadNode *next;
} ReadNode;

ReadNode *load_node(int fd, ReadNode **head);
char *_getline(const int fd);
char *next_line_ptr(char *line);
void free_list(ReadNode **head);

#endif
