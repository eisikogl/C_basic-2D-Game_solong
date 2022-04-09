NAME	= so_long

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

SRCS	= ./srcs/main.c

OBJS	= $(SRCS:%.c=%.o)

$(NAME):$(OBJS)
		make -C ./libs/mlx
		mv ./libs/mlx/libmlx.a ./libmlx.a
		$(CC) $(CFLAGS) $(SRCS) -framework OpenGL -framework AppKit libmlx.a -o $(NAME)

all: 	$(NAME)

clean:
		make -C ./libs/mlx clean
		rm -rf */*.o libmlx.a so_long.o

fclean: clean
		rm -rf so_long

re: 	fclean all

.PHONY: all clean fclean re bonus
