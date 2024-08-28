#include "../includes/cub3d.h"

void	init_game(t_data *d)
{
	d->game->player_x = d->file->map->p_pos_x;
	d->game->player_y = d->file->map->p_pos_y;
}

void	play_game(t_data *d)
{
	init_game(d);
	open_window(d);
	create_game(d);
}
int arguments_and_extension (int argc, char *str, int *error)
{
    if(argc != 2)
	{
		*error = ARG_FAIL;
		return(*error); 
	}
	else if (ft_strlen(str) < 5 || ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4) != 0)
	{
		*error = EXT_ERROR; 
		return(*error); 
	}
	return(0); 
}

int	main(int argc, char **argv)

{
	int		error_code;
	t_data	*d;

	error_code = 0; 
	if(arguments_and_extension(argc,argv[1], &error_code))
		err_free_message(NULL, error_code); 
	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		err_free_message(NULL, ALLOC_FAIL); 
	init_data(d);
	init_map(d,argv[1]);
	play_game(d);
	error_code = d->error;
	free_mlx(d);
	free_data(d);
	return(error_code);
}
