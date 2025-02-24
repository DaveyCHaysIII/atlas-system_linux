CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g3

SOCK := socket_utils.c
PRINT := print_utils.c
PARSE := parse_utils.c

todo_api_0: api_0.c $(SOCK) $(PRINT) $(PARSE)
	@$(CC) $(CFLAGS) $^ -o $@

todo_api_1: api_1.c $(SOCK) $(PRINT) $(PARSE);
	@$(CC) $(CFLAGS) $^ -o $@

todo_api_2: api_2.c $(SOCK) $(PRINT) $(PARSE);
	@$(CC) $(CFLAGS) $^ -o $@

todo_api_3: api_3.c $(SOCK) $(PRINT) $(PARSE);
	@$(CC) $(CFLAGS) $^ -o $@

todo_api_4: api_4.c $(SOCK) $(PRINT) $(PARSE);
	@$(CC) $(CFLAGS) $^ -o $@

todo_api_5: api_5.c $(SOCK) $(PRINT) $(PARSE);
	@$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
