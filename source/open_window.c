#include "../includes/cub3d.h"

int	render_frame(t_data *d)
{
	(void) d;
	return (0);
}

// X button
int	close_game(void *ptr)
{
	t_data *d;

	d = (t_data *)ptr;
	// ft_putstr_fd("game turned off\n", 2)
	write(2, "game turned off\n", 17);
	mlx_loop_end(d->mlx);
	free_data(d);
	exit(0);
}

int	key_handler(int keycode, void *d)
{
	if (keycode == ESC)
		close_game(d);

	return (0);
}

void	open_window(t_data *d)
{
	d->mlx = mlx_init();
	if (d->mlx == NULL)
	{
		// set error
		free_data(d);
		return ;
	}
	mlx_get_screen_size(d->mlx, d->screen_size_x, d->screen_size_y);


	d->win = mlx_new_window(d->mlx, *(d->screen_size_x) *0.5, *(d->screen_size_y) * 0.5, "cub3D");
	if (d->win == NULL)
	{
		//set error
		free_data(d);
		return ;
	}
	mlx_hook(d->win, 17, 1L << 2, &close_game, d);
	mlx_hook(d->win, 2, 1L << 0, &key_handler, d);
	// mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}