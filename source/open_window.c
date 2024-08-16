#include "../includes/cub3d.h"

int	render_frame(t_data *d)
{
	(void) d;
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
	// mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}