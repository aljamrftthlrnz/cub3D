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
	d->win = mlx_new_window(d->mlx, 600, 500, "cub3D");
	if (d->win == NULL)
	{
		//set error
		free_data(d);
		return ;
	}
}
