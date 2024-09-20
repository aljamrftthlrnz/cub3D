#include "../includes/cub3d.h"

void	arrow_keys(t_data *d, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		d->game->p_pos_dir -= 2;
	}
	if (keycode == KEY_RIGHT)
	{
		d->game->p_pos_dir += 2;
	}
	while (d->game->p_pos_dir < 0)
	{
		d->game->p_pos_dir = 360 + d->game->p_pos_dir;
	}
	while (d->game->p_pos_dir > 359)
	{
		d->game->p_pos_dir = d->game->p_pos_dir - 360;
	}
	printf("direction: %d\n", d->game->p_pos_dir); //debugging help
}

void	angle_calc(int angle, int keycode, float *p_left, float *p_right)
{
	float	tmp;

	printf("angle: %d\n", angle); //debugging help
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
	printf("px: %f\npy: %f\n", *p_left, *p_right); //debugging help
}

void	player_step(t_data *d, int keycode)
{
	float	p_left;
	float	p_right;

	angle_calc(d->game->p_pos_dir % 90, keycode, &p_left, &p_right);
	if (d->game->p_pos_dir < 90)
	{
		d->game->pos_x += p_left;
		d->game->pos_y -= p_right;
	}
	else if (d->game->p_pos_dir < 180)
	{
		d->game->pos_x += p_right;
		d->game->pos_y += p_left;
	}
	else if (d->game->p_pos_dir < 270)
	{
		d->game->pos_x -= p_left;
		d->game->pos_y += p_right;
	}
	else if (d->game->p_pos_dir < 360)
	{
		d->game->pos_x -= p_right;
		d->game->pos_y -= p_left;
	}
}