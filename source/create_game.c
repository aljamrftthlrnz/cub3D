#include "../includes/cub3d.h"


//destination image, source image, destination position, source position
void	copy_pos_to_img(t_image *d_img, t_image *s_img, int d_pos, int s_pos)
{
	int	i;

	i = 0;

	while (i < 3)
	{
		d_img->img_adr[d_pos++] = s_img->img_adr[s_pos++];
		i++;
	}
}

// takes img that is to be displayed
// takes h as in height that needs to be displayed
// takes x and y as coordinates where raycasting meets the wall
	// and where it should be displayed
// startx signifies the position of x inside the img_adr that should first be accessed
void	img_dis_col(t_data *d, t_image *img, double h, double x, double y, int startx)
{
	double quo;
	double wall;
	int		upper_y_pos;
	int		source_pos;
	int		dest_pos;

	quo = img->height/h;
	wall = 0;
	upper_y_pos = y - h; 

	if (upper_y_pos < 0)
	{
		wall = (upper_y_pos * (-1)) * quo;
		upper_y_pos = 0;
	}
	while (wall < h)
	{
		/* getting position of source and destination image. */
		source_pos = img_get_pos(img, startx, (int) wall);
		dest_pos = img_get_pos(d->screen, x, upper_y_pos++);
		/* if queried position is outside of range, then -1 is returned and loop will break */
		if (source_pos < 0 || dest_pos < 0)
		{
			// wall += quo; //this lags immensely
			// continue ;
			break ;
		}
		copy_pos_to_img(d->screen, img, dest_pos, source_pos);
		wall += quo;
		// upper_y_pos++;
	}

}


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
	int	texture_segment = d->elem->wallx; //* 64


	int	loop;

	// if (d->ray->mapX % 1 == 0)


	loop = 0;
	
	/* adjusting some variables for "no wall hit" */
	if (d->ray->hit == 0)
	{
		wall_height = 0;
		ray_hit_wall_y = SCREEN_H / 2;
	}
	while (loop < column_width)
	{
		color_above(d, wall_height, ray_hit_wall_x + loop, ray_hit_wall_y);
		color_below(d, ray_hit_wall_x + loop, ray_hit_wall_y);
		if (d->ray->hit == 1)
		{
			img_dis_col(d, &d->NESW[d->elem->texnum], wall_height, ray_hit_wall_x + loop, ray_hit_wall_y, texture_segment);
		}
		
		loop++;
	}
	return ;
}

int	time_to_render(void)
{
	struct timeval	t;
	static long time = 0;
	long	time_new_ms;

	gettimeofday(&t, NULL);
	time_new_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if (time + (1000 / FRMRT) <= time_new_ms)
	{
		time = time_new_ms;
		return (1);
	}
	return (0);
}

int	render_frame(t_data *d)
{
	if (time_to_render() == 1 && d->ray->activate == 1)
	{
		// raycasting(d);
	    ray_loop(d->game, d->ray, d->map, d->elem, d);

		mlx_put_image_to_window(d->mlx, d->win, d->screen->img_ptr, 0, 0);
		d->ray->activate = 0;
	}
	return (0);
}

void	create_game(t_data *d)
{
	setup_key_buttons(d);
	mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}