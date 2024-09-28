#include "../includes/cub3d.h"

/* colors pixels from middle of screen to lower end of screen */
void	color_below(t_data *d, double ray_hit_wall_x, double ray_hit_wall_y)
{
	if (ray_hit_wall_y >= SCREEN_H - 1)
		return ;
	while (ray_hit_wall_y < SCREEN_H)
	{
		pixel_to_img(d->screen, ray_hit_wall_x, ray_hit_wall_y, d->elem->flo_rgb);
		ray_hit_wall_y++;
	}
}


/* colors pixels from middle of screen to upper end of screen */
void	color_above(t_data *d, int wall_height, double ray_hit_wall_x, double ray_hit_wall_y)
{
	int	paint_color;

	paint_color = ray_hit_wall_y - wall_height;
	if (paint_color < 0)
		return ;
	if (paint_color > SCREEN_H) //used to get stuck because paint_color ended up being millions big
		paint_color = SCREEN_H / 2;
	while (paint_color >= 0)
	{
		pixel_to_img(d->screen, ray_hit_wall_x, paint_color, d->elem->ceil_rgb);
		paint_color--;
	}
}
