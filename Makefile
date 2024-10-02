NAME = minishell
#-g -fsanitize=address
CCFLGS = -Wall -Wextra -Werror -g3 -fsanitize=address

CC = cc
LIBFT = libft/libft.a
SRC_FILES = parsing/minishell.c \
	parsing/program.c \
	parsing/get_env.c \
	parsing/parsing.c \
	parsing/split.c \
	parsing/fill_list.c \
	parsing/redirection_node.c \
	parsing/add_token.c \
	parsing/node_list.c \
	parsing/tokens.c \
	parsing/clear.c \
	parsing/errors.c \
	parsing/expander.c \
	parsing/environment.c \
	parsing/rm_quotes.c \
	parsing/clear_all.c \
	builtins/mini_echo.c \
	builtins/mini_cd.c \
	builtins/mini_pwd.c \
	builtins/mini_env.c \
	builtins/mini_export.c \
	builtins/mini_exit.c \
	builtins/mini_unset.c \
	execution/pipex.c \
	execution/pipex_utils.c \
	execution/pipex_utils2.c


OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CCFLGS) $(OBJ_FILES) $(LIBFT) -lreadline  -o $(NAME)

$(LIBFT):
	make -C ./libft
clean:
	rm -f $(OBJ_FILES)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
