#!/usr/bin/make -f

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_${HOSTTYPE}.so

CFLAGS = -Wall -Wextra -Werror -g

SRCS =	malloc \
		ft_free \
		ft_realloc \
		show_alloc_mem

SRC_DIR = ./sources/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
OBJ_FILES = $(SRCS:%=%.o)
SRC_FILES = $(SRCS:%=%.c)


all: obj $(LIBFT) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@echo "START"
	gcc -g -Wall -Werror -Wextra -c -I ./libft/libft.h -I includes  -o $@ -c $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	gcc -g -shared -ldl $(LIBFT) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re
