#include "../includes/cub3d.h"

void	arrow_keys(t_data *d, int keycode)
{
	double radian_angle;
	double	tmp;

	if (keycode == KEY_LEFT)
	{
		d->game->p_pos_dir -= KEY_ROT_ANGL;
		radian_angle = -KEY_ROT_ANGL * (PI / 180);
	}
	if (keycode == KEY_RIGHT)
	{
		d->game->p_pos_dir += KEY_ROT_ANGL;
		radian_angle = KEY_ROT_ANGL * (PI / 180);
	}
	tmp = d->ray->plane_x;
	d->ray->plane_x = d->ray->plane_x * cos(radian_angle) - d->ray->plane_y * sin(radian_angle);
	d->ray->plane_y = tmp * sin(radian_angle) + d->ray->plane_y * cos(radian_angle);
	tmp = d->game->dir_x;
	d->game->dir_x = d->game->dir_x * cos(radian_angle) - d->game->dir_y * sin(radian_angle);
	d->game->dir_y = tmp * sin(radian_angle) + d->game->dir_y * cos(radian_angle);
	while (d->game->p_pos_dir < 0)
		d->game->p_pos_dir = 360 + d->game->p_pos_dir;
	while (d->game->p_pos_dir > 359)
		d->game->p_pos_dir = d->game->p_pos_dir - 360;
}

void	normalize_vector(float *x, float *y)
{
	float  magnitude;

	magnitude = sqrt(*x * *x + *y * *y);
	if (magnitude == 0)
		return ;
	else if (magnitude != 1)
	{
		*x = *x * (1 / magnitude);
		*y = *y * (1 / magnitude);
		magnitude = sqrt(*x * *x + *y * *y);
	}
}

void	angle_calc(int angle, int keycode, float *p_left, float *p_right)
{
	float	tmp;

	*p_left = (float) angle / 9 / 10;
	*p_right = 1 - *p_left;
	if (keycode == KEY_S)
	{
		*p_left = *p_left * (-1);
		*p_right = *p_right * (-1);
	}
	if (keycode == KEY_A)
	{
		tmp = *p_left;
		*p_left = *p_right  * (-1);
		*p_right = tmp;
	}
	if (keycode == KEY_D)
	{
		tmp = *p_left;
		*p_left = *p_right;
		*p_right = tmp * (-1);
	}
	normalize_vector(p_left, p_right);
}

// px and py are player position
// cx and cy are center/corner position
float	point_calc(float px, float py, float cx, float cy)
{
	float sq_x;
	float sq_y;

	sq_x = (px - cx) * (px - cx);
	sq_y = (py - cy) * (py - cy);
	printf("distance: %f\n", sqrtf(sq_x + sq_y));
	return (sqrtf(sq_x + sq_y));
}

// if result of point calc is smaller than r (radius)
	// then player is inside corner radius -> no move possible return 1
int	corner_in_circle(t_data *d, float y, float x)
{
	float	og_x;
	float	og_y;

	og_x = x;
	og_y = y;
	if (fmodf(y, 1) > 0.5)
		y = ceilf(y);
	else
		y = floorf(y) - 0.001;
	if (fmodf(x, 1) > 0.5)
		x = ceilf(x);
	else
		x = floorf(x) - 0.001;
	
	if ((d->map->map[(int) og_y][(int) x] == '1' && d->map->map[(int) y][(int) og_x] == '1') || d->map->map[(int) og_y][(int) og_x] == '1')
	{
		if (point_calc(og_x, og_y, x, y) < 0.1)
			return (1);
	}
	return (0);
}

void	check_step_1(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 0 && d->game->p_pos_dir < 90))
		return ;
	if (d->map->map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x + p_left * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y - p_right * (KEY_STP_SIZ),  d->game->pos_x + p_left * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if(d->map->map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ))][(int)(d->game->pos_x + p_left * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x += p_left * KEY_STP_SIZ;
			d->game->pos_y -= p_right * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	check_step_2(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 90 && d->game->p_pos_dir < 180))
		return ;
	if (d->map->map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x + p_right * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y + p_left * (KEY_STP_SIZ),  d->game->pos_x + p_right * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if(d->map->map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ))][(int)(d->game->pos_x + p_right * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x += p_right * KEY_STP_SIZ;
			d->game->pos_y += p_left * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	check_step_3(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 180 && d->game->p_pos_dir < 270))
		return ;
	if (d->map->map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x - p_left * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y  + p_right * (KEY_STP_SIZ),  d->game->pos_x  - p_left * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if(d->map->map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ))][(int)(d->game->pos_x - p_left * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x -= p_left * KEY_STP_SIZ;
			d->game->pos_y += p_right * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	check_step_4(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 270 && d->game->p_pos_dir < 360))
		return ;
	if (d->map->map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x - p_right * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y  - p_left * (KEY_STP_SIZ),  d->game->pos_x  - p_right * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if(d->map->map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ))][(int)(d->game->pos_x - p_right * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x -= p_right * KEY_STP_SIZ;
			d->game->pos_y -= p_left * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	player_step(t_data *d, int keycode)
{
	float	p_left;
	float	p_right;

	angle_calc(d->game->p_pos_dir % 90, keycode, &p_left, &p_right);

	check_step_1(d, p_right, p_left);
	check_step_2(d, p_right, p_left);
	check_step_3(d, p_right, p_left);
	check_step_4(d, p_right, p_left);
}
