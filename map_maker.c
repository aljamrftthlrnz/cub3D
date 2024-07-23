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

void	draw_player(t_data *d)
{
	mlx_pixel_put(d->mlx, d->win, d->map->player_x + 1, d->map->player_y + 1, mlx_get_color_value(d->mlx, 0xcd5c5c));
	mlx_pixel_put(d->mlx, d->win, d->map->player_x , d->map->player_y + 1, mlx_get_color_value(d->mlx, 0xcd5c5c));
	mlx_pixel_put(d->mlx, d->win, d->map->player_x + 1, d->map->player_y , mlx_get_color_value(d->mlx, 0xcd5c5c));
	mlx_pixel_put(d->mlx, d->win, d->map->player_x , d->map->player_y , mlx_get_color_value(d->mlx, 0xcd5c5c));
	// mlx_put_image_to_window(d->mlx, d->win, d->map->img_WE, d->map->player_x, d->map->player_y);
}

void	draw_perspective(t_data *d)
{
	int	sight;
	int	x;
	int y;

	sight = 0;
	x = d->map->player_x;
	y = d->map->player_y;

	while (sight < 32 * 2)
	{
		sight++;
		if (d->map->matrix[(y - 1) / 32][x / 32] != '1')
		{
			mlx_pixel_put(d->mlx, d->win, x , y-- , mlx_get_color_value(d->mlx, 0xcd5c5c));
		}
		else
		{
			break;
		}
	}
}

int	render_frame(t_data *d)
{
	draw_map(d);
	draw_player(d);
	draw_perspective(d);
	return (0);
}