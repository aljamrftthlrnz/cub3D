# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luca <luca@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 11:26:55 by lknobloc          #+#    #+#              #
#    Updated: 2024/07/22 19:43:44 by luca             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = myprogram2


SRC = 	experimenting.c utils.c mock_map.c map_maker.c

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
CC = cc

.PHONY: all fclean re

all:	$(NAME)
debug: CFLAGS += -g 
debug: $(NAME)

$(NAME):	$(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lmlx -L /usr/lib -lXext -lX11 -lm -lbsd -lz 

$(OBJ):	$(SRC) 
	$(CC) $(CFLAGS) $(SRC) -I/usr/include -Imlx -c 

bonus:	all

clean:
	rm -f $(OBJ) 

fclean:	clean
	rm -f $(NAME)

re:	fclean all