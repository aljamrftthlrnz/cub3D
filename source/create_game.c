#include "../includes/cub3d.h"

int	render_frame(t_data *d)
{
	// d->NESW[1]
	(void) d;

	return (0);
}

void	create_game(t_data *d)
{
	setup_key_buttons(d);
	mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}
