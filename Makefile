SRC_FILES= pipex.c ft_split.c ft_substr.c ft_strlen.c get_cmd.c get_path.c exec_error.c
SRC_B_FILES= pipex_bonus.c ft_split_bonus.c ft_substr_bonus.c ft_strlen_bonus.c get_cmd_bonus.c get_path_bonus.c \
			get_next_line_bonus.c get_next_line_utils_bonus.c str_check_bonus.c exec_error.c
SRC=$(addprefix src/, $(SRC_FILES))
SRC_B=$(addprefix src_bonus/, $(SRC_B_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_DIR=obj
OBJ_B=$(addprefix obj_bonus/, $(SRC_B_FILES:.c=.o))
OBJ_B_DIR=obj_bonus
NAME=pipex

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) -o $(NAME)

bonus: $(OBJ_B_DIR) $(OBJ_B)
	make OBJ="$(OBJ_B)" all

obj/%.o: src/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

obj_bonus/%.o: src_bonus/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_B_DIR):
	mkdir $(OBJ_B_DIR)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
