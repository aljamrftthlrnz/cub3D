#include "../includes/cub3d.h"

int	render_frame(t_data *d)
{
	static long l = 0;

	// d->NESW[1]

	mlx_put_image_to_window(d->mlx, d->win, d->NESW[0].img_ptr, 200, 200);


	usleep(50000);
	printf("%ld\n", l);
	l++;


	(void) d;

	return (0);
}

void	create_game(t_data *d)
{
	setup_key_buttons(d);
	mlx_loop_hook(d->mlx, render_frame, d);
	mlx_loop(d->mlx);
}
