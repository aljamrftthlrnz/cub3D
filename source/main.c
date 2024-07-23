#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	int		error_code;
	t_data	*d;

	error_code = 0; 
	if(argc == 2)
	{
	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		return (1);
		
	}
	init_data(d);
	error_code = d->error;
	free_data(d);
	return (error_code);
}