NAME = cub3D
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = -L./inc/mlx -lmlx -lXext -lX11 -lm -lz
INCLUDES = inc/mlx/libmlx.a
SRC = src/*.c

all: $(NAME)

mlx:
	./inc/mlx
	make -C ./inc/mlx

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all