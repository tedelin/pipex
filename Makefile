# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 10:52:51 by tedelin           #+#    #+#              #
#    Updated: 2023/02/11 19:47:09 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include -I./libft
SRC = $(addprefix src/mandatory/, pipex.c utils.c main.c)
OBJ = $(addprefix obj/, pipex.o utils.o main.o)
SRC_BONUS = $(addprefix src/bonus/, pipex_bonus.c utils_bonus.c lst_pid.c main_bonus.c)
OBJ_BONUS = $(addprefix obj/, pipex_bonus.o utils_bonus.o lst_pid.o main_bonus.o)
LIBFT = -Llibft -lft

all: $(NAME)

libft/libft.a:
	make -C libft

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBFT) -o $@

bonus: $(OBJ_BONUS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_BONUS) $(LIBFT) -o $(NAME)

obj/%.o: src/mandatory/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

obj/%.o: src/bonus/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	make -C libft clean
	rm -f $(OBJ) $(OBJS_BONUS)
	rm -rf obj

fclean:	clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re