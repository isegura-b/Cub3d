NAME = cub3D

CC = cc
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = inc/mlx
CFLAGS = #-Wall -Wextra -Werror -g -fsanitize=address
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: mlx $(NAME)

mlx:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all