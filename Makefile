CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx
RM = rm -f

NAME = fractol
HEADER = fractol.h

SRCS =	fractol.c calculations.c mouse.c

OBJS = $(SRCS:.c=.o)
MINILIBX = ./mlx/libmlx.a

%.o:%.c 	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: 		mlxrule $(NAME)

mlxrule:
	make -C ./mlx

$(NAME): 	$(OBJS) $(MINILIBX)
			$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
			make clean -C ./mlx
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
