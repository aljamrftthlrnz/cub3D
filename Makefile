NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra


FILES = 	main.c \
		utils_free.c init_data.c \
		open_window.c
SRC = $(addprefix source/, $(FILES))
OBJ = $(SRC:%.c=%.o)

LIBFT = includes/libft
MLXINC = -I/usr/include -Imlx
MLXLNK = -lmlx -L /usr/lib -lXext -lX11 -lm -lbsd -lz

.PHONY: all fclean re

all:	$(NAME)
debug: CFLAGS += -g 
debug: $(NAME)

$(NAME):	$(OBJ) 
	cd $(LIBFT) && make
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT)/libft.a $(OBJ) $(MLXLNK) 

%.o: %.c
	$(CC) $(CFLAGS) $(MLXINC) -c $< -o $@ 

bonus:	all

clean:
	rm -f $(OBJ) 
	cd $(LIBFT) && make clean

fclean:	clean
	rm -f $(NAME)
	cd $(LIBFT) && make fclean

re:	fclean all