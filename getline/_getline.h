#ifndef MAIN_H
#define MAIN_H

#define READ_SIZE 1024

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
