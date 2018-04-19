NAME = malloc

FLAGS = -Wall -Werror -Wextra -g

CC = gcc

SOURCES =	main 

INCLUDES =	malloc.h

LIB =	libft/libft.a

RM = rm -Rf

$(NAME):
	$(CC) $(FLAGS) -c $(addsuffix .c,$(SOURCES))
	$(CC) $(addsuffix .o,$(SOURCES)) -I$(INCLUDES) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(addsuffix .o,$(SOURCES))

fclean: clean
	$(RM) $(NAME)

re: fclean all%