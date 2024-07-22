#include "cub3d.h"

void	free_data(t_data *d)
{
	if (d->win)
	{
		mlx_destroy_window(d->mlx, d->win);
	}
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	free(d);
}

void init_map(t_map *map)
{
	map->ceiling_color = NULL;
	map->floor_color = NULL;
	map->img_EA = NULL;
	map->img_NO = NULL;
	map->img_WE = NULL;
	map->img_SO = NULL;
	map->matrix = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
}
