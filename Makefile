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
		srcs/gaming/move_player.c \
		srcs/gaming/init_textures.c \
		srcs/gaming/init_player.c \
		srcs/gaming/the_game.c
FLAGS = -Wall -Wextra -Werror -g3
HEADER_FILE = ./includes
HEADERS =	$(HEADER_FILE)/cub.h \
			$(HEADER_FILE)/libft.h
LIB_DIR = libft
LIB_NAME = libft.a
OBJS = ${SRCS:.c=.o}

.PHONY: all
.PHONY: clean
.PHONY: fclean
.PHONY: re

$(NAME): $(OBJS) $(LIB_NAME)
	clang $(OBJS) $(LIB_NAME) -o $(NAME) -lm -lmlx -lXext -lX11

$(OBJS): %.o: %.c $(HEADERS)
	clang $(FLAGS) -I$(HEADER_FILE) -c $< -o $@

$(LIB_NAME):
	cd $(LIB_DIR) && make all
	cp $(LIB_DIR)/$(LIB_NAME) .

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(LIB_NAME)
	cd $(LIB_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIB_DIR) && make fclean

re: fclean all