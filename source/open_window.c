#include "../includes/cub3d.h"

// initializes mlx and window; sets up key handling; starts the loop
void	open_window(t_data *d)
{
	d->win = mlx_new_window(d->mlx, 600, 500, "cub3D");
	if (d->win == NULL)
	{
		free_mlx(d);
		err_free_message(d, MLXWI);
		return ;
	}
}
