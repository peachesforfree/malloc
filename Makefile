NAME = malloc.exe

FILE		=	main \
				malloc

OBJFILES	= $(FILE:%=%.o)
SRCFILES	= $(FILE:%=%.c)
SRC			= $(addprefix sources/,$(SRCFILES))
OBJ			= $(addprefix obj/,$(OBJFILES))
CC			= gcc
FLAGS		= -g -Wextra -Wall -Werror
INC			= -I libft/inc -I includes/
LIB			= -L libft/

all:$(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

objdir:
	mkdir -p obj/

obj/%.o: $(SRC) | objdir
	mkdir -p obj/ && $(CC) $(FLAGS) -c $< -o $@ $(INC)

rmobj:
	rm -rf obj/

rmbin:
	rm -rf $(NAME)

again: rmobj rmbin all

clean: rmobj
	make clean -C libft/

fclean: clean rmbin
	make fclean -C libft/

re: fclean all
