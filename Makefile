NAME = mini

CCFLGS = -Wall -Wextra -Werror  -fsanitize=address -g
CC = cc
SRC_FILE =main.c \
	tst.c
OBJ = $(SRC_FILE : .o:.c)


%.o: %.c
	 $(CC) $(CCFLGS) 

all: $(NAME)

$(NAME):  $(SRC_FILE) $(OBJ)
	 $(CC) $(CCFLGS) $(SRC_FILE) $(OBJ)  -o $(NAME)


clean: $(OBJ) 
	rm -rf $(OBJ) 
fclean: clean
	rm -rf $(NAME) 
re:fclean all