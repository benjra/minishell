NAME = minishell
#-g -fsanitize=address
CCFLGS = -Wall -Wextra -Werror 

CC = cc
LIBFT = our_libft/libft.a
SRC_FILES = parsing/minishell.c \
	parsing/get_env.c \
	parsing/parsing.c \
	parsing/split.c \
	parsing/fill_list.c \
	parsing/node_list.c \
	parsing/redirection_node.c \
	parsing/add_token.c \
	parsing/tokens.c \
	parsing/errors.c \
	parsing/expander_utils.c \
	parsing/expand.c \
	parsing/environment.c \
	parsing/rm_quotes.c \
	parsing/clear_all.c \
	parsing/get_word.c \
	parsing/search_env.c \
	parsing/split_utils.c \
	parsing/token_node.c \
	builtins/mini_echo.c \
	builtins/mini_cd.c \
	builtins/mini_pwd.c \
	builtins/mini_env.c \
	builtins/mini_export.c \
	builtins/mini_exit.c \
	builtins/mini_unset.c \
	builtins/env_utils.c \
	execution/pipex.c \
	execution/init_fnct.c \
	execution/pipex_utils1.c \
	execution/pipex_utils2.c \
	execution/pipex_utils3.c \
	execution/pipex_utils4.c \
	execution/pipex_utils5.c \
	execution/pipex_utils6.c \
	execution/pipex_utils7.c \
	execution/pipex_utils8.c \
	execution/pipex_utils9.c \
	builtins/cd_utils.c	\
	builtins/export_utils1.c \
	builtins/export_utils2.c \
	builtins/export_utils3.c

OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CCFLGS) $(OBJ_FILES) $(LIBFT) -lreadline  -o $(NAME)

$(LIBFT):
	make -C ./our_libft
clean:
	rm -f $(OBJ_FILES)
	make -C ./our_libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./our_libft fclean

re: fclean all
