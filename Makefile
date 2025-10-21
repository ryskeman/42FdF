# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fernando <fernando@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 17:44:36 by fernafer          #+#    #+#              #
#    Updated: 2025/10/15 21:28:22 by fernando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- PROJECT INFO ---
NAME = fdf
CC = cc

# --- LIBRARIES ---
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

# --- SOURCES ---
SRCS = main.c \
		#parsing_map.c \
		#draw.c \

OBJS	= $(SRCS:.c=.o)

# --- FLAGS ---
CFLAGS = -Wall -Wextra -Werror
INCLUDES =  -Iincludes/ -I$(LIBFT_DIR)/ -I$(MLX_DIR)/
MLX_FLAGS = -lXext -lX11
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -lm


# FLAG FOR DEBUGGING ---
FSANITIZE = -fsanitize=address -g3


# --- RULES ---
all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	@echo "🔗	Linking $(NAME)..."
	#$(CC) $(OBJS) $(LIBFT) $(LFLAGS) $(FSANITIZE) -o $(NAME)
	$(CC) $(OBJS) $(LIBFT) $(LFLAGS) $(FSANITIZE) -o $(NAME)
	@echo "✅ $(NAME) compiled succesfully!"

# MiniLibX COMPILING RULE
$(MLX_LIB):
	@echo "🛠️  Compiling MiniLibX..."
	@make -C $(MLX_DIR)

# LIBFT COMPILING RULE
$(LIBFT):
	@echo "🛠️	Compiling Libft..."
	@make -C $(LIBFT_DIR)

# RULE TO CREATE OBJECTS
%.o: %.c
	@echo "⚙️	Compiling $< into $@"
	$(CC) $(CFLAGS) $(FSANITIZE) $(INCLUDES) -c $< -o $@

# CLEANING OBJECTS RULE
clean:
	@echo "🧹	Cleaning object files..."
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Clean complete."

# CLEANING FILES RULE
fclean: clean
	@echo "🔥	Deep cleaning executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Deep clean complete."

re: fclean all
	@echo "Rebuilding project..."


.PHONY: all clean fclean re

