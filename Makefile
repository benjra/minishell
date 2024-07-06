NAME = mini

CCFLGS = -Wall -Wextra -Werror -fsanitize=address -g
CC = cc
LIBFT=libft/libft.a
SRC_FILES = minishell.c \
	program.c \
	get_env.c \
	prompt.c \
	utils.c \
	parsing.c \
	main.c

OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CCFLGS) $(OBJ_FILES)  -lreadline $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C /.libft
clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
