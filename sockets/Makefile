CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99

UTIL := utils.c

todo_api_0: api_0.c $(UTIL)
	@rm -f $@
	@$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
