#include "../includes/cub3d.h"

void	init_game(t_data *d)
{
	d->game->p_pos_dir = d->map->p_pos_dir;
	d->game->pos_x = d->map->pos_x + 0.5;
	d->game->pos_y = d->map->pos_y + 0.5;
	d->mlx = mlx_init();
	if (d->mlx == NULL)
	{
		err_free_message(d, MLXIN);
		return ;
	}
}

void	play_game(t_data *d)
{
	init_game(d);
	init_img(d);
	init_raycasting(d->ray, d->game);
	open_window(d);
	create_game(d);
}

int	arguments_and_extension(int argc, char *str, int *error)
{
	if (argc != 2)
	{
		*error = ARG_FAIL;
		return (*error);
	}
	else if (ft_strlen(str) < 5 || ft_strncmp(str + ft_strlen(str) - 4, \
		".cub", 4) != 0)
	{
		*error = EXT_ERROR;
		return (*error);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;
	int		error_code;

	error_code = 0;
	if (arguments_and_extension(argc, argv[1], &error_code))
		err_free_message(NULL, error_code);
	init_data(&d);
	init_map(&d, argv[1]);
	play_game(&d);
	// possibly add for funcheck issue
	//free_data(&d); 
	return (error_code);
}
