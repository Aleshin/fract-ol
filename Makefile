CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx
RM = rm -f

NAME = fractol
HEADER = fractol.h

SRCS =	fractol.c calculations.c

OBJS = $(SRCS:.c=.o)

%.o:%.c 	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
