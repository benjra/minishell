NAME = minishell

CCFLGS = -Wall -Wextra -Werror -fsanitize=address -g
CC = cc
LIBFT = libft/libft.a
SRC_FILES = ./parsing/minishell.c \
	./parsing/program.c \
	./parsing/get_env.c \
	./parsing/prompt.c \
	./parsing/utils.c \
	./parsing/parsing.c \
	./parsing/main.c \
	./execution/mini_cd.c \
	./execution/mini_echo.c \
	./execution/mini_env.c \
	./execution/mini_exit.c \
	./execution/mini_export.c \
	./execution/mini_pwd.c \
	./execution/mini_unset.c

OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CCFLGS) $(OBJ_FILES) $(LIBFT)  -lreadline  -o $(NAME)

$(LIBFT):
	make -C libft
clean:
	rm -f $(OBJ_FILES)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
