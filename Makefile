SRC_FILES= pipex.c
SRC= $(addprefix src/, $(SRC_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
NAME=pipex

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) -o $(NAME)

obj/%.o: src/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
