NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g


FILES = main.c init_data.c init_map.c init_map_helper.c \
		input_first.c input_second.c error.c create_map.c \
		check_map.c check_map_2.c \
		raycast.c raycast_loop.c raycast_texture.c \
		images.c \
		open_window.c create_game.c \
		render_column.c render_c_f.c \
		key_handler.c player_movement.c \
		init_img.c img_utils.c \
		anti_island_checker.c
	
SRC = $(addprefix source/, $(FILES))
OBJ = $(SRC:%.c=%.o)

LIBFT = ./includes/libft
MLXINC = -I/usr/include -Imlx
MLXLNK = -lmlx -L /usr/lib -lXext -lX11 -lm -lbsd -lz

.PHONY: all fclean re

all:	$(NAME)

$(NAME):	$(OBJ) 
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -o $(NAME) $(MLXLNK) 

%.o: %.c
	$(CC) $(CFLAGS) $(MLXINC) -c $< -o $@ 

bonus:	all

clean:
	rm -f $(OBJ) 
	@make -C $(LIBFT) clean

fclean:	clean
	rm -f $(NAME)
	@make -C $(LIBFT) fclean
	

debug: CFLAGS += -g 
debug: $(NAME)

re:	fclean all