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
		srcs/pars.c
FLAGS = -Wall -Wextra -Werror
HEADER = ./includes
LIB_DIR = libft
LIB_NAME = libft.a
OBJS = ${SRCS:.c=.o}

.PHONY: all
.PHONY: clean
.PHONY: fclean
.PHONY: re

$(NAME): $(OBJS) $(LIB_NAME)
	clang $(OBJS) $(LIB_NAME) -o $(NAME)

%.o: %.c
	clang $(FLAGS) -c $< -o $@

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