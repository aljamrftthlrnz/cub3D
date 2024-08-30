
#ifndef CUB3D_H
# define CUB3D_H
//# include "./utils/get_next_line.h"
//# include "./utils/libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <math.h>

//pre-release libs
# include <stdio.h>
# include <string.h>
// # include <std.h>

# define PIX 32
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

// directions
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

// typedef struct s_map;
typedef struct s_map
{
	void	*img_NO;
	void	*img_SO;
	void	*img_WE;
	void	*img_EA;
	void	*img_new;

	int		*floor_color;
	int		*ceiling_color;
	char	**matrix;
	int		map_width;
	int		map_height;
	float		player_x;
	float		player_y;
	char	player_dir;
	int		player_sight;
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	
	char	*img_adr;


}	t_image;
typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	int		error;
	t_image	*img;
}	t_data;



// experimenting.c
int	mini_close_game(int keycode, void *mlx);
int	mini_close_game_2(void *ptr);
void	free_data(t_data *d);
int	main(void);

//mock_map.c
char **fill_mock_map(void);
int	init_mock_map(t_data *d);

//utils.c
void	free_data(t_data *d);
void init_map(t_map *map);

// map_maker.c
int	draw_tile(t_data *d, int x, int y);
int	draw_map(t_data *d);
int	render_frame(t_data *d);

// keyhandler.c
void	step_forward(t_data *d, int key);
int wasd_keys(void *ptr, int key);
void	arrow_keys(t_data *d, int keycode);
int	mini_key_handle(int keycode, void *mlx);


#endif
