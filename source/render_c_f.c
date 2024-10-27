#include "../includes/cub3d.h"

/* colors pixels from middle of screen to lower end of screen */
void	color_below(t_data *d, double ray_hit_wall_x, double ray_hit_wall_y)
{
	if (ray_hit_wall_y >= SCREEN_H - 1)
		return ;
	if (ray_hit_wall_y < 0)
	{
		ray_hit_wall_y = SCREEN_H / 2;
	}
	while (ray_hit_wall_y < SCREEN_H)
	{
		pixel_to_img(d->screen, ray_hit_wall_x, ray_hit_wall_y, \
			d->elem->flo_rgb);
		ray_hit_wall_y++;
	}
}

/* colors pixels from middle of screen to upper end of screen */
void	color_above(t_data *d, int wa_height, double wall_x, double wall_y)
{
	int	paint_color;

	paint_color = wall_y - wa_height;
	if (paint_color < 0)
		return ;
	if (paint_color > SCREEN_H)
		paint_color = SCREEN_H / 2;
	while (paint_color >= 0)
	{
		pixel_to_img(d->screen, wall_x, paint_color, d->elem->ceil_rgb);
		paint_color--;
	}
}
