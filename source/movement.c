#include "../includes/cub3d.h"

void	normalize_vector(float *x, float *y)
{
	float	magnitude;

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
		*p_left = *p_right * (-1);
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

static void	angle(t_data *d, double radian_angle)
{
	double	tmp;

	tmp = d->ray->plane_x;
	d->ray->plane_x = d->ray->plane_x * cos(radian_angle) \
		- d->ray->plane_y * sin(radian_angle);
	d->ray->plane_y = tmp * sin(radian_angle) \
		+ d->ray->plane_y * cos(radian_angle);
	tmp = d->game->dir_x;
	d->game->dir_x = d->game->dir_x * cos(radian_angle) \
		- d->game->dir_y * sin(radian_angle);
	d->game->dir_y = tmp * sin(radian_angle) \
		+ d->game->dir_y * cos(radian_angle);
}

void	arrow_keys(t_data *d, int keycode)
{
	double	radian_angle;

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
	angle(d, radian_angle);
	while (d->game->p_pos_dir < 0)
		d->game->p_pos_dir = 360 + d->game->p_pos_dir;
	while (d->game->p_pos_dir > 359)
		d->game->p_pos_dir = d->game->p_pos_dir - 360;
}
