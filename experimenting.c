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
int	mini_key_handle(int keycode, void *mlx)
{
	if (keycode == ESC)
		mini_close_game(1, mlx);
	return 0;
}

void	free_data(t_data *d)
{
	if (d->win)
	{
		mlx_destroy_window(d->mlx, d->win);
	}
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	free(d);
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
	d->win = mlx_new_window(d->mlx, 5 * 32, 5 * 32, "window_name");
	if (d->win == NULL)
	{
		free_data(d);
		return (1);
	}
	mlx_key_hook(d->win, mini_key_handle, d);
	// mlx_loop_hook(mlx, NULL, NULL);
	mlx_loop(d->mlx);
	free_data(d);
	return (0);

}