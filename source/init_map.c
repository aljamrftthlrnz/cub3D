#include "../includes/cub3d.h"

// uses *d as a flag: if actual data struct was given as parameter 
	// array will be allocated
	// if instead NULL is given, no extra allocations
void	replace_initial_player_pos(t_map *m)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	c = m->map[m->pos_y][m->pos_x];
	while (m->map[i] != NULL)
	{
		j = 0;
		while (m->map[i][j] != '\0')
		{
			if (m->map[i][j] == c)
			{
				m->map[i][j] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
}

int	get_map_length(char **map)
{
	int	y;

	y = 0;
	while (map && map[y])
	{
		y++;
	}
	return (y);
}

int	get_map_width(char **map)
{
	int	y;
	int	max_x;

	y = 0;
	max_x = 0;
	while (map && map[y])
	{
		if (max_x < (int) ft_strlen(map[y]))
			max_x = ft_strlen(map[y]);
		y++;
	}
	return (max_x);
}

void	init_map(t_data *d, char *argv)
{
	t_map	*map;

	map = d->map;
	if (get_dimensions_of_file(d, argv))
		err_free_message(d, FILE_EMPTY);
	if (create_file_array(d, argv))
		err_free_message(d, FILE_EMPTY);
	if (extract_textures(d, d->file_arr))
		err_free_message(d, IDENT_W);
	if (!d->elem->no_path || !d->elem->so_path || !d->elem->we_path \
		|| !d->elem->ea_path)
		err_free_message(d, PERS_M);
	if (!d->elem->flo_rgb || !d->elem->ceil_rgb)
		err_free_message(d, FL_CEIL_M);
	if (process_map(d))
		err_free_message(d, MISSING_MAP);
	if (check_order_of_map(d))
		err_free_message (d, ORDER);
	map_related_checks(d, map);
	replace_initial_player_pos(d->map);
	d->map->width = get_map_width(d->map->map);
	d->map->length = get_map_length(d->map->map);
	anti_island_checker(d, d->map);
}
