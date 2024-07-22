
#ifndef CUB3D_H
# define CUB3D_H
//# include "./utils/get_next_line.h"
//# include "./utils/libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>


# define ESC 65307
typedef struct s_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	int		error;
}	t_data;

typedef struct s_map
{
	void	*path_NO;
	void	*path_SO;
	void	*path_WE;
	void	*path_EA;
	int		*floor_color;
	int		*ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;


// experimenting.c
int	mini_close_game(int keycode, void *mlx);
int	mini_key_handle(int keycode, void *mlx);
void	free_data(t_data *d);
int	main(void);


#endif
