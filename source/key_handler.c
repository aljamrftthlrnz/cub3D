#include "../includes/cub3d.h"

// closes game on X button or ESC key
int	close_game(void *ptr)
{
	t_data *d;

	d = (t_data *)ptr;
	// ft_putstr_fd("game turned off\n", 2)
	write(2, "game turned off\n", 17);
	mlx_loop_end(d->mlx);
	free_mlx(d);
	free_data(d);
	exit(0);
}

void	arrow_keys(t_data *d, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		d->game->player_dir -= 2;
	}
	if (keycode == KEY_RIGHT)
	{
		d->game->player_dir += 2;
	}
	while (d->game->player_dir < 0)
	{
		d->game->player_dir = 360 + d->game->player_dir;
	}
	while (d->game->player_dir > 359)
	{
		d->game->player_dir = d->game->player_dir - 360;
	}
	printf("direction: %d\n", d->game->player_dir); //debugging help
}

void	player_step(t_data *d, int keycode)
{
		int	angle = d->game->player_dir % 90;
	float	p_left;
	float	p_right;

	if (keycode != KEY_W)
		return ;
	printf("angle: %d\n", angle);
	p_left = (float) angle / 9 / 10;
	p_right = 1 - p_left;
	printf("px: %f\npy: %f\n", p_left, p_right);

	if (d->game->player_dir < 90)
	{
		d->game->player_x += p_left;
		d->game->player_y -= p_right;
	}
	else if (d->game->player_dir < 180)
	{
		d->game->player_x += p_right;
		d->game->player_y += p_left;
	}
	else if (d->game->player_dir < 270)
	{
		d->game->player_x -= p_left;
		d->game->player_y += p_right;
	}
	else if (d->game->player_dir < 360)
	{
		d->game->player_x -= p_right;
		d->game->player_y -= p_left;
	}
}

// handles all key presses
int	key_handler(int keycode, void *d)
{
	if (keycode == ESC)
		close_game(d);
	if (keycode == KEY_W)
	{
		player_step(d, keycode);
		return (0);
	}
	if (keycode == KEY_A)
		return (0);
	if (keycode == KEY_S)
		return (0);
	if (keycode == KEY_D)
		return (0);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		arrow_keys(d, keycode);
		return (0);
	}
	return (0);
}

void	setup_key_buttons(t_data *d)
{
	mlx_hook(d->win, 17, 1L << 2, &close_game, d);
	mlx_hook(d->win, 2, 1L << 0, &key_handler, d);
}
