#include "../includes/cub3d.h"
/* 
void	copy_column_to_img(t_data *d, t_image *img)
{

}

//copy the img from NESW to screen
void	make_texture_bigger(t_data *d, t_image *img, int height, int width)
{
	float quo;
	float p;

	quo = img->height/height;
	p = 0;
	while (p < height)
	{
		copy_column_to_img(d, img);
		p += quo;
	}


} */

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
/* 
void	color_below(t_data *d, float ray_hit_wall_x, float ray_hit_wall_y)
{
	if (ray_hit_wall_y >= SCREEN_H - 1)
		return ;
	while (ray_hit_wall_y < SCREEN_H)
	{
		
		ray_hit_wall_y++;
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
	int	ray_hit_wall_y = 400; //delete/replace
	int	wall_height = 150; //delete/replace

	int	texture_segment = 0; // this is where the ray hits the texture... zero means on the left most, 32 in the middle, 63 is the right most

	int	loop;

	loop = 0;
	while (loop < column_width)
	{
		color_above(d, wall_height, ray_hit_wall_x + loop, ray_hit_wall_y);
		color_below(d, ray_hit_wall_x + loop, ray_hit_wall_y);
		img_dis_col(d, &d->NESW[0], wall_height, ray_hit_wall_x + loop, ray_hit_wall_y, texture_segment);
		loop++;
	}

	return ;
}
 */
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
	// time = time_new_ms;
	return (0);
}

int	render_frame(t_data *d)
{
	static long l = 0;
	static int height = 64;
	static int width = 64;
	// int bg_color[3] = {12, 20, 28};
	int i;

	i = 0;

	// render_column(d);



	// d->NESW[1]

	// fill_color_img(d->screen, bg_color);
	while (i < 64)
	{
		img_dis_col(d, &d->NESW[0], height, 100 + i, 400, i);
		i++;
	}
/* 	i = 0;
	while (i < 64)
	{
		img_dis_col(d, &d->NESW[1], height, 170 + i, 400, i);
		i++;
	}
	i = 0;
	while (i < 64)
	{
		img_dis_col(d, &d->NESW[2], height, 240 + i, 400, i);
		i++;
	}
	i = 0;
	while (i < 64)
	{
		img_dis_col(d, &d->NESW[3], height, 310 + i, 400, i);
		i++;
	} */
	// make_texture_bigger(d, &d->NESW[0], height, width);
	height++;
	width++;
	if (height > 200 || width > 200)
	{
		height = 64;
		width = 64;
	}

	// mlx_put_image_to_window(d->mlx, d->win, d->NESW[0].img_ptr, 200, 200);

	if (time_to_render() == 1)
	{
		mlx_put_image_to_window(d->mlx, d->win, d->screen->img_ptr, 0, 0);
		//render
		printf("renders\n");
	}

	// usleep(50000);
	// printf("%ld\n", l);
	l++;


	(void) d;

	return (0);
}

void	create_game(t_data *d)
{
	setup_key_buttons(d);
	mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}
