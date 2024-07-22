#include "cub3d.h"

int	mini_close_game(int keycode, void *ptr)
{
	t_data *d;

	d = (t_data *)ptr;
	(void)keycode;
	write(2, "game turned off\n", 17);

	mlx_loop_end(d->mlx);
	free_data(d);
	exit(0);
}

int wasd_keys(void *d, int key)
{
	t_data *data;

	data = (t_data *)d;
	if (key == W)
	{
		data->map->player_y -= 1;
	}
	if (key == A)
	{
		data->map->player_x -= 1;
	}
	if (key == S)
	{
		data->map->player_y += 1;
	}
	if (key == D)
	{
		data->map->player_x += 1;
	}
	return (0);
}

int	mini_key_handle(int keycode, void *d)
{
	if (keycode == ESC)
		mini_close_game(1, d);
	if (keycode == W)
		wasd_keys(d, W);
	if (keycode == A)
		wasd_keys(d, A);
	if (keycode == S)
		wasd_keys(d, S);
	if (keycode == D)
		wasd_keys(d, D);
	return 0;
}




int	main(void)
{
	t_data *d;

	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		return (1);
	d->mlx = mlx_init();
	if (d->mlx == NULL)
	{
		free_data(d);
		return (1);
	}
	if (init_mock_map(d) != 0)
	{
		free_data(d);
		return (1);
	}
	d->win = mlx_new_window(d->mlx, d->map->map_width * 32, d->map->map_height * 32, "window_name");
	if (d->win == NULL)
	{
		free_data(d);
		return (1);
	}
	mlx_key_hook(d->win, mini_key_handle, d);
	mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
	free_data(d);
	return (0);

}