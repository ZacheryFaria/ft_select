CC=gcc
CFLAGS=-Werror -Wextra -Wall -g -Ilibft/ -I.
LIBFLAGS=-L libft/ -lft  -lcurses
NAME=ft_select
SRC=$(wildcard src/*)
OBJ=$(SRC:src/%.c=%.o)
SHELL := /bin/bash

.PHONY: clean fclean all re norm norme debug test norman

VPATH = src obj libft/includes include

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) -o $(NAME) obj/* $(LIBFLAGS)
	@echo "ft_select build complete!"

all: $(NAME)

%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o obj/$@ -c $<

clean:
	@make -C libft/ clean
	@rm -rf obj/

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

norm:
	norminette src/. includes/.

norme: norm

norman:
	-norminette * | grep -iv warning
