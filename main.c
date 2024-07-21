#include "cub3d.h"

int	main(void)
{
	t_data *d;

	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		return (1);
	free_data(d);
	return (0);
}