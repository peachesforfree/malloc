NAME = malloc.exe

CFLAGS = -Wall -Wextra -Werror -g


OBJ_FILES = $(SRCS:%=%.o)
SRC_FILES = $(SRCS:%=%.c)
SRCS =	main \
		malloc 
SRC_DIR = ./sources/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)


all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	gcc $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	gcc $(OBJ) $(LIBFT) -lm -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re
