NAME = mini

CCFLGS = -Wall -Wextra -Werror #-fsanitize=address -g
CC = cc
SRC_FILES = minishell.c \
	program.c \
	get_env.c \
	utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)

%.o: %.c
	$(CC) $(CCFLGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CCFLGS) $(OBJ_FILES)  -lreadline -o $(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
