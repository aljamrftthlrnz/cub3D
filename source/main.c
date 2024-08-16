#include "../includes/cub3d.h"

void	play_game(t_data *d)
{
	open_window(d);
	create_game(d);
}

int	main(void)
{
	int		error_code;
	t_data	*d;

	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		return (1);
	init_data(d);
	play_game(d);
	error_code = d->error;
	free_data(d);
	return (error_code);
}
