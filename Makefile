# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 17:44:36 by fernafer          #+#    #+#              #
#    Updated: 2025/11/07 19:13:08 by fernafer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- PROJECT INFO ---
NAME = fdf
CC = cc
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus

# --- LIBRARIES ---
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_OBJ_DIR = $(MLX_DIR)/obj

# --- SOURCES ---
SRCS =  main.c \
		cleanup.c \
		parsing_map.c \
		draw.c \
		hooks.c \
		utils.c \
		bresenham.c \

SRCS_BONUS = main_bonus.c \
		cleanup_bonus.c \
		parsing_map_bonus.c \
		draw_bonus.c \
		hooks_bonus.c \
		utils_bonus.c \
		bresenham_bonus.c \

SRC= $(addprefix src/, $(SRCS))
SRC_BONUS= $(addprefix bonus/, $(SRCS_BONUS))

OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJ_DIR_BONUS)/, $(SRCS_BONUS:.c=.o))

# --- FLAGS ---
CFLAGS = -Wall -Wextra -Werror
INCLUDES =  -Iincludes/ -I$(LIBFT_DIR)/ -I$(MLX_DIR)/
MLX_FLAGS = -lXext -lX11
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -lm


# FLAG FOR DEBUGGING ---
FSANITIZE = -fsanitize=address -g3


# --- RULES ---
all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJ_DIR) $(OBJS)
	@echo "🔗	Linking $(NAME)..."
	$(CC) $(OBJS) $(LIBFT) $(LFLAGS) $(FSANITIZE) -o $(NAME)
	@echo "✅ $(NAME) compiled succesfully!"

# BONUS RULE
bonus: $(NAME)_bonus

$(NAME)_bonus: $(MLX_LIB) $(LIBFT) $(OBJ_DIR_BONUS) $(OBJS_BONUS)
	@echo "🔗	Linking $(NAME)_bonus..."
	$(CC) $(OBJS_BONUS) $(LIBFT) $(LFLAGS) $(FSANITIZE) -o $(NAME)_bonus
	@echo "✅ $(NAME)_bonus compiled succesfully!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

# MiniLibX COMPILING RULE
$(MLX_LIB):
	@echo "🛠️  Compiling MiniLibX..."
	@make -C $(MLX_DIR)

# LIBFT COMPILING RULE
$(LIBFT):
	@echo "🛠️	Compiling Libft..."
	@make -C $(LIBFT_DIR)

# RULE TO CREATE OBJECTS
$(OBJ_DIR)/%.o: src/%.c $(OBJ_DIR)
	@echo "⚙️	Compiling $< into $@ (in $(OBJ_DIR)/)"
	$(CC) $(CFLAGS) $(FSANITIZE) $(INCLUDES) -c $< -o $@

# RULE TO CREATE BONUS OBJECTS
$(OBJ_DIR_BONUS)/%.o: bonus/%.c $(OBJ_DIR_BONUS)
	@echo "⚙️	Compiling $< into $@ (in $(OBJ_DIR_BONUS)/)"
	$(CC) $(CFLAGS) $(FSANITIZE) $(INCLUDES) -c $< -o $@

# CLEANING OBJECTS RULE
clean:
	@echo "🧹	Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@rm -rf *.o
	@rm -rf $(MLX_OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "Clean complete."

# CLEANING FILES RULE
fclean: clean
	@echo "🔥	Deep cleaning executable..."
	@rm -f $(NAME) $(NAME)_bonus
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	@echo "Deep clean complete."

re: fclean all
	@echo "Rebuilding project..."


.PHONY: all clean fclean re bonus

