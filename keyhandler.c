
#include "cub3d.h"

void	step_forward(t_data *d, int key)
{
	int	angle = d->map->player_sight % 90;
	float	p_left;
	float	p_right;
	float	tmp;

	printf("angle: %d\n", angle);
	p_left = (float) angle / 9 / 10;
	p_right = 1 - p_left;
	if (key == S)
	{
		p_left = p_left * (-1);
		p_right = p_right * (-1);
	}
	if (key == A)
	{
		tmp = p_left;
		p_left = p_right  * (-1);
		p_right = tmp;
	}
	if (key == D)
	{
		tmp = p_left;
		p_left = p_right;
		p_right = tmp * (-1);
	}
	printf("px: %f\npy: %f\n", p_left, p_right);


	if (d->map->player_sight < 90)
	{
		d->map->player_x += p_left;
		d->map->player_y -= p_right;
	}
	else if (d->map->player_sight < 180)
	{
		d->map->player_x += p_right;
		d->map->player_y += p_left;
	}
	else if (d->map->player_sight < 270)
	{
		d->map->player_x -= p_left;
		d->map->player_y += p_right;
	}
	else if (d->map->player_sight < 360)
	{
		d->map->player_x -= p_right;
		d->map->player_y -= p_left;
	}
}

int wasd_keys(void *ptr, int key)
{
	t_data *d;
	// float	step_x;
	// float	step_y;

	d = (t_data *)ptr;
	if (key == W || key == S || key == A || key == D)
	{
		step_forward(d, key);
	}
	return (0);
}

void	arrow_keys(t_data *d, int keycode)
{
	if (keycode == LEFT)
	{
		d->map->player_sight -= 2;
	}
	if (keycode == RIGHT)
	{
		d->map->player_sight += 2;
	}
	while (d->map->player_sight < 0)
		d->map->player_sight = 360 + d->map->player_sight;
	while (d->map->player_sight > 359)
		d->map->player_sight = d->map->player_sight - 360;
	printf("direction: %d\n", d->map->player_sight);
}

int	mini_key_handle(int keycode, void *d)
{
	if (keycode == ESC)
		mini_close_game_2(d);
	if (keycode == W)
		wasd_keys(d, W);
	if (keycode == A)
		wasd_keys(d, A);
	if (keycode == S)
		wasd_keys(d, S);
	if (keycode == D)
		wasd_keys(d, D);
	if (keycode == LEFT || keycode == RIGHT)
		arrow_keys(d, keycode);


	return 0;
}