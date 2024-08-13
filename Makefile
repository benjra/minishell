NAME = minishell

CCFLGS = -Wall -Wextra -Werror -g3 -fsanitize=address 
CC = cc
LIBFT = libft/libft.a
SRC_FILES = parsing/minishell.c \
	parsing/program.c \
	parsing/get_env.c \
	parsing/prompt.c \
	parsing/utils.c \
	parsing/parsing.c \
	parsing/split.c \
	parsing/fill_list.c \
	parsing/tokens.c \
	parsing/clear.c \
	parsing/errors.c \
	parsing/expander.c \
	parsing/envirement.c \
	parsing/rm_quotes.c \
	parsing/clear_all.c

OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CCFLGS) $(OBJ_FILES) $(LIBFT)  -lreadline  -o $(NAME)

$(LIBFT):
	make -C /libft
clean:
	rm -f $(OBJ_FILES)
	make -C /libft clean

fclean: clean
	rm -f $(NAME)
	make -C /libft fclean

re: fclean all
