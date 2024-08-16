#include "../includes/cub3d.h"

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