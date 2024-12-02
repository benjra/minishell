NAME = libft.a
CCF = cc -Wall -Wextra -Werror 
Fun = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isascii.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_memset.c \
		ft_memmove.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_itoa.c \
		ft_split.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_striteri.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strcmp.c
		
FunBon = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c


OBJBONU = $(FunBon:.c=.o)	

OBJ = $(Fun:.c=.o)

all: $(NAME)

$(NAME):
		$(CCF) -c $(Fun)
		ar rcs $(NAME) $(OBJ)

bonus : $(OBJBONU) 

$(OBJBONU) : $(FunBon)
		$(CCF) -c $(FunBon)
		ar rcs $(NAME) $(OBJBONU)

clean:
		rm -rf $(OBJ) $(OBJBONU)
fclean: clean
		rm -rf $(NAME)
re: fclean all

