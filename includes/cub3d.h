
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
#include "libft/libft.h"

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
}	t_data;

// main.c
int		main(void);

// utils_free.c
void	free_data(t_data *d);

// init_data.c
void	init_data(t_data *d);


#endif