# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 08:28:02 by fyuzhyk           #+#    #+#              #
#    Updated: 2022/10/18 13:44:56 by fyuzhyk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = SRC_DIR

CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=address -g

SRC = src/main.c

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

debug :
	$(MAKE) CFLAGS="-g" re

$(NAME) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJ)

re : fclean all
