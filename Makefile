NAME = cub3D
SRC = 	main.c \
		utils_free.c init_data.c

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
MLXINC = -I/usr/include -Imlx
MLXLNK = -lmlx -L /usr/lib -lXext -lX11 -lm -lbsd -lz
CC = cc

.PHONY: all fclean re

all:	$(NAME)
debug: CFLAGS += -g 
debug: $(NAME)

$(NAME):	$(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLXLNK) 

$(OBJ):	$(SRC) 
	$(CC) $(CFLAGS) $(SRC) $(MLXINC) -c 

bonus:	all

clean:
	rm -f $(OBJ) 

fclean:	clean
	rm -f $(NAME)

re:	fclean all