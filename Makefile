SRC_FILES= pipex.c ft_split.c ft_substr.c ft_strlen.c get_cmd.c get_path.c
SRC_B_FILES= pipex_bonus.c ft_split_bonus.c ft_substr_bonus.c ft_strlen_bonus.c get_cmd_bonus.c get_path_bonus.c ft_strncmp_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
SRC=$(addprefix src/, $(SRC_FILES))
SRC_B=$(addprefix src_bonus/, $(SRC_B_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_B=$(addprefix obj_bonus/, $(SRC_B_FILES:.c=.o))
NAME=pipex

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) -o $(NAME)

bonus: $(OBJ_B)
	gcc -Wall -Werror -Wextra $(OBJ_B) -o $(NAME)

obj/%.o: src/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

obj_bonus/%.o: src_bonus/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
