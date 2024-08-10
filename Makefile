NAME = minishell

CCFLGS = -Wall -Wextra -Werror -g3 -fsanitize=address 
CC = cc
LIBFT = libft/libft.a
SRC_FILES = minishell.c \
	program.c \
	get_env.c \
	prompt.c \
	utils.c \
	parsing.c \
	split.c \
	fill_list.c \
	tokens.c \
	clear.c \
	errors.c \
	expander.c \
	envirement.c \
	rm_quotes.c

OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CCFLGS) $(OBJ_FILES) $(LIBFT)  -lreadline  -o $(NAME)

$(LIBFT):
	make -C ./libft
clean:
	rm -f $(OBJ_FILES)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
