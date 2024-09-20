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
void	img_dis_col(t_data *d, t_image *img, float h, float x, float y, int startx)
{
	float quo;
	float wall;
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
		source_pos = img_get_pos(img, startx, (int) wall);
		dest_pos = img_get_pos(d->screen, x, upper_y_pos++);
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

void	color_below(t_data *d, float ray_hit_wall_x, float ray_hit_wall_y)
{
	if (ray_hit_wall_y >= SCREEN_H - 1)
		return ;
	while (ray_hit_wall_y < SCREEN_H)
	{
		pixel_to_img(d->screen, ray_hit_wall_x, ray_hit_wall_y, d->file->elem->flo_rgb);
		ray_hit_wall_y++;
	}
}

void	color_above(t_data *d, int wall_height, float ray_hit_wall_x, float ray_hit_wall_y)
{
	if (ray_hit_wall_y - wall_height < 0)
		return ;
	while (ray_hit_wall_y - wall_height >= 0)
	{
		pixel_to_img(d->screen, ray_hit_wall_x, ray_hit_wall_y - wall_height, d->file->elem->ceil_rgb);
		ray_hit_wall_y--;
	}
}

// this function will take the raycasting struct and render entire column
	// texture (N)
	// floor and ceiling
	// correct width
void	render_column(t_data *d)
{
	int column_width = 10; //delete/replace later with actual width from struct or define
	int	ray_hit_wall_x = 400; //delete/replace
	int	ray_hit_wall_y = 500; //delete/replace
	int	wall_height = 150; //delete/replace

	int	texture_segment = 0; // this is where the ray hits the texture... zero means on the left most, 32 in the middle, 63 is the right most

	int	loop;

	loop = 0;
	while (loop < column_width)
	{
		color_above(d, wall_height, ray_hit_wall_x + loop, ray_hit_wall_y);
		color_below(d, ray_hit_wall_x + loop, ray_hit_wall_y);
		img_dis_col(d, &d->NESW[1], wall_height, ray_hit_wall_x + loop, ray_hit_wall_y, texture_segment);
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
	if (time_to_render() == 1)
	{
		//render
		render_column(d);
		mlx_put_image_to_window(d->mlx, d->win, d->screen->img_ptr, 0, 0);
		printf("renders\n");
	}
	return (0);
}

void	create_game(t_data *d)
{
	setup_key_buttons(d);
	mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}