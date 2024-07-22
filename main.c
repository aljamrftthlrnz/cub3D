#include "cub3d.h"

int	main(void)
{
	int		error_code;
	t_data	*d;

	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		return (1);
	init_data(d);
	error_code = d->error;
	free_data(d);
	return (error_code);
}