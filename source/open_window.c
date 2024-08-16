#include "../includes/cub3d.h"

// initializes mlx and window; sets up key handling; starts the loop
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
}
