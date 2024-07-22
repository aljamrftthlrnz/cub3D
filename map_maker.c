#include "cub3d.h"

int	draw_tile(t_data *d, int x, int y)
{
	if (d->map->matrix[y][x] == '1')
		mlx_put_image_to_window(d->mlx, d->win, d->map->img_EA, x * 32, y * 32);
	if (d->map->matrix[y][x] == '0')
		mlx_put_image_to_window(d->mlx, d->win, d->map->img_NO, x * 32, y * 32);
	if (d->map->matrix[y][x] == 'N')
	{
		// if (d->map->player_x == 0 && d->map->player_y == 0)
		// {
		// 	d->map->player_x = x * 32 + 16;
		// 	d->map->player_y = y * 32 + 16;
		// }
		mlx_put_image_to_window(d->mlx, d->win, d->map->img_WE, x * 32, y * 32);
	}
	mlx_pixel_put(d->mlx, d->win, d->map->player_x + 1, d->map->player_y + 1, mlx_get_color_value(d->mlx, 0xcd5c5c));
	mlx_pixel_put(d->mlx, d->win, d->map->player_x , d->map->player_y + 1, mlx_get_color_value(d->mlx, 0xcd5c5c));
	mlx_pixel_put(d->mlx, d->win, d->map->player_x + 1, d->map->player_y , mlx_get_color_value(d->mlx, 0xcd5c5c));
	mlx_pixel_put(d->mlx, d->win, d->map->player_x , d->map->player_y , mlx_get_color_value(d->mlx, 0xcd5c5c));
	// if (d->map->matrix[y][x] == 'N')
	// 	mlx_put_image_to_window(d->mlx, d->win, d->map->img_WE, x * 32, y * 32);


	return (0);
}

int	draw_map(t_data *d)
{
	int	x = 0;
	int y = 0;

	while (x < d->map->map_width && y < d->map->map_height)
	{
		draw_tile(d, x, y);
		x++;
		if (x == d->map->map_width)
		{
			x = 0;
			y++;
		}
	}
	return (0);
}


int	render_frame(t_data *d)
{
	draw_map(d);
	return (0);
}