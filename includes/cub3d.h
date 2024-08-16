
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
#include "libft/libft.h"


# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_element
{
	char			*we_path;
	char			*so_path;
	char			*no_path;
	char			*ea_path;
	int				*ceil_rgb;
	int				*flo_rgb;
	struct s_file	*file;
}	t_element;

typedef struct s_map
{
	char			**map;
	char			**cpy_map;
	int				length;
	int				width;
	int				p_pos_y;
	int				p_pos_x;
	struct s_file	*file;
} t_map;

typedef struct s_file 
{
	struct s_data	*data; // Use Forward declaration, is only init further down
	t_element		*elem;
	t_map			*map;
}	t_file; 

typedef struct s_data
{
	void	*mlx;
	void	*win; 
	int		error;
	char	**file_arr; 
	int		y_file; 
	int		x_file;
	t_file	*file; 


	int	screen_size_x[1];
	int	screen_size_y[1];
}	t_data;

// main.c
int		main(void);
void	play_game(t_data *d);

// open_window.c
int	render_frame(t_data *d);
int	close_game(void *ptr);
int	key_handler(int keycode, void *d);
void	open_window(t_data *d);


// utils_free.c
void	free_data(t_data *d);

// init_data.c
void	init_data(t_data *d);


#endif