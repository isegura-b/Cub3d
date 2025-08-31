# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 08:58:22 by isegura-          #+#    #+#              #
#    Updated: 2025/08/22 11:58:15 by isegura-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
MANDATORY_SRC_DIR = mandatory/src
BONUS_SRC_DIR = bonus/src
OBJ_DIR = obj
MANDATORY_OBJ_DIR = $(OBJ_DIR)/mandatory
BONUS_OBJ_DIR = $(OBJ_DIR)/bonus
MLX_DIR = inc/mlx
BONUS_MLX_DIR = inc/mlx

CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz #-fsanitize=address
BONUS_LFLAGS = -L$(BONUS_MLX_DIR) -lmlx -lXext -lX11 -lm -lz -fsanitize=address

MANDATORY_SRC = \
	$(MANDATORY_SRC_DIR)/check_map.c \
	$(MANDATORY_SRC_DIR)/clean.c \
	$(MANDATORY_SRC_DIR)/dda.c \
	$(MANDATORY_SRC_DIR)/events.c \
	$(MANDATORY_SRC_DIR)/gnl_cub_utils.c \
	$(MANDATORY_SRC_DIR)/gnl_cub.c \
	$(MANDATORY_SRC_DIR)/init.c \
	$(MANDATORY_SRC_DIR)/main.c \
	$(MANDATORY_SRC_DIR)/parse_info_file.c \
	$(MANDATORY_SRC_DIR)/parsing_utils.c \
	$(MANDATORY_SRC_DIR)/parsing_utils2.c \
	$(MANDATORY_SRC_DIR)/parsing.c \
	$(MANDATORY_SRC_DIR)/render_tex.c \
	$(MANDATORY_SRC_DIR)/draw_no_wall.c \
	$(MANDATORY_SRC_DIR)/render.c \
	$(MANDATORY_SRC_DIR)/save_info_file.c \
	$(MANDATORY_SRC_DIR)/save_into_file_utils.c \
	$(MANDATORY_SRC_DIR)/utils.c \
	$(MANDATORY_SRC_DIR)/utils2.c \
	$(MANDATORY_SRC_DIR)/utils3.c

BONUS_SRC = \
	$(BONUS_SRC_DIR)/check_map_bonus.c \
	$(BONUS_SRC_DIR)/clean_bonus.c \
	$(BONUS_SRC_DIR)/dda_bonus.c \
	$(BONUS_SRC_DIR)/draw_no_wall_bonus.c \
	$(BONUS_SRC_DIR)/events_bonus.c \
	$(BONUS_SRC_DIR)/gnl_cub_bonus.c \
	$(BONUS_SRC_DIR)/gnl_cub_utils_bonus.c \
	$(BONUS_SRC_DIR)/init_bonus.c \
	$(BONUS_SRC_DIR)/main_bonus.c \
	$(BONUS_SRC_DIR)/minimap_bonus.c \
	$(BONUS_SRC_DIR)/minimap2_bonus.c \
	$(BONUS_SRC_DIR)/parse_info_file_bonus.c \
	$(BONUS_SRC_DIR)/parsing_bonus.c \
	$(BONUS_SRC_DIR)/parsing_utils2_bonus.c \
	$(BONUS_SRC_DIR)/parsing_utils_bonus.c \
	$(BONUS_SRC_DIR)/render_bonus.c \
	$(BONUS_SRC_DIR)/render_tex_bonus.c \
	$(BONUS_SRC_DIR)/save_info_file_bonus.c \
	$(BONUS_SRC_DIR)/save_into_file_utils_bonus.c \
	$(BONUS_SRC_DIR)/utils_bonus.c \
	$(BONUS_SRC_DIR)/utils2_bonus.c \
	$(BONUS_SRC_DIR)/utils3_bonus.c

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
	-@$(MAKE) -C $(BONUS_MLX_DIR) clean

fclean: clean
	@echo "Removing executables..."
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all 
