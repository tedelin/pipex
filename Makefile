# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 10:52:51 by tedelin           #+#    #+#              #
#    Updated: 2023/02/08 19:50:12 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include -I./libft
SRC = $(addprefix src/mandatory/, pipex.c utils.c main.c)
OBJ = $(addprefix obj/, pipex.o utils.o main.o)
SRC_BONUS = $(addprefix src/bonus/, pipex_bonus.c utils_bonus.c main_bonus.c)
OBJ_BONUS = $(addprefix obj/, pipex_bonus.o utils_bonus.o main_bonus.o)
LIBFT_LIB = libft/libft.a
LIBFT_PATH = libft

all: $(NAME) $(NAME_BONUS)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

obj/%.o: src/mandatory/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

obj/%.o: src/bonus/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJ)
	rm -rf obj

fclean:	clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re