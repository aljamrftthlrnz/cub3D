#include "../includes/cub3d.h"



// takes img that is to be displayed
// takes h as in height that needs to be displayed
// takes x and y as coordinates where raycasting meets the wall
	// and where it should be displayed
// startx signifies the position of x inside the img_adr that should first be accessed
// paints the texture from the upper edge to the lower edge
void	img_dis_col(t_data *d, double h, double x, double y)
{
	double quo;
	double wall;
	int		upper_y_pos;
	int		source_pos;
	int		dest_pos;

	quo = d->NESW[d->elem->texnum].height / h;
	wall = 0;
	upper_y_pos = y - h;
	if (upper_y_pos < 0)
	{
		wall = upper_y_pos * (-1) / 2 / h * 64;
		upper_y_pos = 0;
	}
	while (upper_y_pos <= y && wall <= d->NESW[d->elem->texnum].height)
	{
		source_pos = img_get_pos(&d->NESW[d->elem->texnum], (int) ((double) d->elem->wallx * 100 * 0.63), (int) wall);
		dest_pos = img_get_pos(d->screen, x, upper_y_pos++);
		if (source_pos < 0 || dest_pos < 0)
		{
			break ;
		}
		copy_pos_to_img(d->screen, &d->NESW[d->elem->texnum], dest_pos, source_pos);
		wall += quo;
	}
}

// this function will take values from raycasting struct 
		//and render entire column
void	render_column(t_data *d, int x)
{
	int	ray_hit_wall_y;
	int	wall_height;
	int	loop;

	loop = 0;
	ray_hit_wall_y = d->elem->drawEnd;
	wall_height = d->elem->line_height;
	if (d->ray->hit == 0)
	{
		wall_height = 0;
		ray_hit_wall_y = SCREEN_H / 2;
	}
	while (loop < LINE_W)
	{
		if (d->elem->line_height < SCREEN_H || d->ray->hit == 0)
			color_above(d, wall_height, x + loop, ray_hit_wall_y);
		if (d->ray->hit == 1)
			img_dis_col(d, wall_height, x + loop, ray_hit_wall_y);
		if (d->elem->line_height < SCREEN_H || d->ray->hit == 0)
			color_below(d, x + loop, ray_hit_wall_y);
		loop++;		
	}
	return ;
}
