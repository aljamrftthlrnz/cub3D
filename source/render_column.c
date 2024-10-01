#include "../includes/cub3d.h"



// takes img that is to be displayed
// takes h as in height that needs to be displayed
// takes x and y as coordinates where raycasting meets the wall
	// and where it should be displayed
// startx signifies the position of x inside the img_adr that should first be accessed
// paints the texture from the upper edge to the lower edge
void	img_dis_col(t_data *d, t_image *img, double h, double x, double y, int startx)
{
	double quo;
	double wall;

	int		upper_y_pos;
	int		source_pos;
	int		dest_pos;

	quo = img->height/h;
	wall = 0;
	upper_y_pos = y - h; //+ 1; 
	if (upper_y_pos < 0)
	{
		wall = upper_y_pos * (-1) / 2 / h * 64;
		upper_y_pos = 0;
	}
	while (wall < h && wall < img->height)
	{
		/* getting position of source and destination image. */
		source_pos = img_get_pos(img, startx, (int) wall);
		dest_pos = img_get_pos(d->screen, x, upper_y_pos++);
		/* if queried position is outside of range, then -1 is returned and loop will break */
		if (source_pos < 0 || dest_pos < 0)
		{
			printf("skips at x==%f y==%f //startx==%d wall==%f...s==%d d==%d\n", x, y, startx, wall, source_pos, dest_pos);
			break ;
		}
		copy_pos_to_img(d->screen, img, dest_pos, source_pos);
		wall += quo;
		// upper_y_pos++;
	}

}

// this function will take the raycasting struct and render entire column
	// texture (N)
	// floor and ceiling
	// correct width
void	render_column(t_data *d, int x)
{
	int column_width = LINE_W; //delete/replace later with actual width from struct or define


	/* coordinates where ray hits the wall */
	int	ray_hit_wall_x = x; //delete/replace
	int	ray_hit_wall_y = d->elem->drawEnd; //delete/replace
	// int	ray_hit_wall_y = (SCREEN_H - d->elem->line_height) / 2 + d->elem->line_height; //delete/replace
	

	/* wall/line height */
	int	wall_height = d->elem->line_height; //delete/replace
	// int	wall_height = d->ray->perpWallDist; //delete/replace


	/* this is the x coordinate of the texture */
	/* expected input: zero means on the left most, 32 in the middle, 63 is the right most */
	double	texture_segment = d->elem->wallx; //* 64


	int	loop;


	loop = 0;
	
	/* adjusting some variables for "no wall hit" */
	if (d->ray->hit == 0)
	{
		wall_height = 0;
		ray_hit_wall_y = SCREEN_H / 2;
	}
	while (loop < column_width)
	{
		if (d->elem->line_height < SCREEN_H || d->ray->hit == 0)
			color_above(d, wall_height, ray_hit_wall_x + loop, ray_hit_wall_y);
		if (d->ray->hit == 1)
		{
			img_dis_col(d, &d->NESW[d->elem->texnum], wall_height, ray_hit_wall_x + loop, ray_hit_wall_y, (int) (texture_segment * 100 * 0.64));
		}
		if (d->elem->line_height < SCREEN_H || d->ray->hit == 0)
			color_below(d, ray_hit_wall_x + loop, ray_hit_wall_y);
		
		loop++;
	}
	return ;
}