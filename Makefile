NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
MANDATORY_SRC_DIR = mandatory/src
BONUS_SRC_DIR = bonus/src
OBJ_DIR = obj
MANDATORY_OBJ_DIR = $(OBJ_DIR)/mandatory
BONUS_OBJ_DIR = $(OBJ_DIR)/bonus
MLX_DIR = mandatory/inc/mlx
BONUS_MLX_DIR = bonus/inc/mlx

CFLAGS = -fsanitize=address #-Wall -Wextra -Werror -g
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -fsanitize=address
BONUS_LFLAGS = -L$(BONUS_MLX_DIR) -lmlx -lXext -lX11 -lm -lz -fsanitize=address

MANDATORY_SRC = $(wildcard $(MANDATORY_SRC_DIR)/*.c)
BONUS_SRC = $(wildcard $(BONUS_SRC_DIR)/*.c)
MANDATORY_OBJ = $(patsubst $(MANDATORY_SRC_DIR)/%.c, $(MANDATORY_OBJ_DIR)/%.o, $(MANDATORY_SRC))
BONUS_OBJ = $(patsubst $(BONUS_SRC_DIR)/%.c, $(BONUS_OBJ_DIR)/%.o, $(BONUS_SRC))

.PHONY: all bonus clean fclean re mlx bonus_mlx

all: mlx $(NAME)

bonus: bonus_mlx $(BONUS_NAME)

mlx:
	@echo "Compiling MLX for mandatory..."
	@$(MAKE) -C $(MLX_DIR)

bonus_mlx:
	@echo "Compiling MLX for bonus..."
	@$(MAKE) -C $(BONUS_MLX_DIR)

$(NAME): $(MANDATORY_OBJ)
	@echo "Linking mandatory version..."
	@$(CC) $(MANDATORY_OBJ) -o $(NAME) $(LFLAGS)
	@echo "Mandatory version compiled successfully!"

$(BONUS_NAME): $(BONUS_OBJ)
	@echo "Linking bonus version..."
	@$(CC) $(BONUS_OBJ) -o $(BONUS_NAME) $(BONUS_LFLAGS)
	@echo "Bonus version compiled successfully!"

$(MANDATORY_OBJ_DIR)/%.o: $(MANDATORY_SRC_DIR)/%.c
	@mkdir -p $(MANDATORY_OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(BONUS_MLX_DIR) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@rm -rf mandatory/obj
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(BONUS_MLX_DIR) clean

fclean: clean
	@echo "Removing executables..."
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all 