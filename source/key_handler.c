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
		d->map->player_dir -= 2;
	}
	if (keycode == KEY_RIGHT)
	{
		d->map->player_dir += 2;
	}
	while (d->map->player_dir < 0)
	{
		d->map->player_dir = 360 + d->map->player_dir;
	}
	while (d->map->player_dir > 359)
	{
		d->map->player_dir = d->map->player_dir - 360;
	}
	printf("direction: %d\n", d->map->player_dir); //debugging help
}

// handles all key presses
int	key_handler(int keycode, void *d)
{
	if (keycode == ESC)
		close_game(d);
	if (keycode == KEY_W)
		return (0);
	if (keycode == KEY_A)
		return (0);
	if (keycode == KEY_S)
		return (0);
	if (keycode == KEY_D)
		return (0);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		return (0);
	return (0);
}

void	setup_key_buttons(t_data *d)
{
	mlx_hook(d->win, 17, 1L << 2, &close_game, d);
	mlx_hook(d->win, 2, 1L << 0, &key_handler, d);
}
