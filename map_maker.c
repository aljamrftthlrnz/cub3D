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
/* void	draw_perspective_trig(t_data *d)
{
	float	sight;
	float	x;
	float y;
	float opposite;
	float	hypothenuse;
	float rad;

	sight = 0;
	x = d->map->player_x;
	y = d->map->player_y;
	rad = d->map->player_sight * 0.017453;
	while (sight < 32 * 2)
	{
		sight += 0.1;
		if (d->map->player_sight == 0)
			y--;
		else if (d->map->player_sight == 90)
			x++;
		else if (d->map->player_sight == 180)
			y++;
		else if (d->map->player_sight == 270)
			x--;
		else
		{
			opposite = tanf(rad) * sight;
			if (opposite < 0)
				opposite = opposite * (-1);	
			hypothenuse = opposite / sinf(rad);
			// printf("sight: %f\nangle: %d\nopposite: %f\nhypothenuse: %f\n", sight, d->map->player_sight, opposite, hypothenuse);
		}
		if (d->map->player_sight > 180 && d->map->player_sight < 360)
			x = x - opposite;
		else
			x = x + opposite;

		if (d->map->player_sight > 90 && d->map->player_sight < 270)
			y = y + sight;
		else
			y = y - sight;

		if (d->map->matrix[(int) y / 32][(int) x / 32] != '1')
		{
			// printf("\nx: %d\ny: %d\n", x, y);
			mlx_pixel_put(d->mlx, d->win, x , y , mlx_get_color_value(d->mlx, 0xcd5c5c));
		}
		else
		{
			break;
		}
	}
	(void) hypothenuse;
} */



/* void	draw_perspective(t_data *d)
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
} */

// draw_perspective(t_data *d)
// {

// }

int	render_frame(t_data *d)
{

	// usleep(1000000);
	// draw_map(d);
	// draw_player(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img->img_ptr, 0, 0);
	// draw_perspective(d);
	return (0);
}