CFLAGS := -Wall -Werror -Wextra -pedantic -g3

CC := gcc

NAME := 0-hreadelf

SRC := $(wildcard *.c)

.PHONY := all clean

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -f $(NAME)
