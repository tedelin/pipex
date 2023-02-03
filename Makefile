# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 10:52:51 by tedelin           #+#    #+#              #
#    Updated: 2023/02/03 13:55:35 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include -I./libft
SRC = $(addprefix src/, pipex.c main.c)
OBJ = $(addprefix obj/, pipex.o main.o)
LIBFT_LIB = libft/libft.a
LIBFT_PATH = libft

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJ)
	rm -rf obj

fclean:	clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re