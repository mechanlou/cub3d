# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkowalsk <rkowalsk@student.le-101.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 14:32:57 by rkowalsk          #+#    #+#              #
#    Updated: 2020/02/18 16:46:24 by rkowalsk         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
SRCS =	srcs/cub.c \
		srcs/parsing/pars.c \
		srcs/parsing/pars_file.c \
		srcs/parsing/pars_path_window.c \
		srcs/parsing/pars_rgb.c \
		srcs/parsing/pars_map.c \
		srcs/parsing/store_page.c \
		srcs/parsing/utils_tools_params.c \
		srcs/parsing/utils.c \
		srcs/gaming/key_hook.c \
		srcs/gaming/ray_casting.c \
		srcs/gaming/sprites.c \
		srcs/gaming/show_game.c \
		srcs/gaming/move_player.c \
		srcs/gaming/init_textures.c \
		srcs/gaming/init_player.c \
		srcs/gaming/create_bmp.c \
		srcs/gaming/create_image.c \
		srcs/gaming/take_screenshot.c \
		srcs/gaming/sprites_screenshot.c \
		srcs/gaming/add_sprite_dist.c \
		srcs/gaming/the_game.c
FLAGS = -Wall -Wextra -Werror -g3
HEADER_FILE = ./includes
HEADERS =	$(HEADER_FILE)/cub.h \
			$(HEADER_FILE)/libft.h
LIB_DIR = libft
LIB_NAME = libft.a
MLX_DIR = mlx
MLX_NAME = libmlx.a
OBJS = ${SRCS:.c=.o}

.PHONY: all
.PHONY: clean
.PHONY: fclean
.PHONY: re

$(NAME): $(OBJS) $(LIB_NAME) $(MLX_NAME)
	clang $(OBJS) $(LIB_NAME) $(MLX_NAME) -o $(NAME) -lm -lX11 -lXext

$(OBJS): %.o: %.c $(HEADERS)
	clang $(FLAGS) -I$(HEADER_FILE) -c $< -o $@

$(LIB_NAME):
	make -C $(LIB_DIR) all
	cp $(LIB_DIR)/$(LIB_NAME) .

$(MLX_NAME):
	make -C $(MLX_DIR) all
	cp $(MLX_DIR)/$(MLX_NAME) .

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(LIB_NAME)
	rm -f $(MLX_NAME)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIB_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all