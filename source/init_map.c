#include "../includes/cub3d.h"

// uses *d as a flag: if actual data struct was given as parameter 
	// array will be allocated
	// if instead NULL is given, no extra allocations
int	setup_file(t_data *d, int *fd, char **line, char *argv)
{
	*fd = open(argv, O_RDONLY);
	if (*fd < 0)
		return (1);
	*line = get_next_line(*fd);
	if (!*line)
	{
		close (*fd);
		return (1);
	}
	if (d != NULL)
	{
		d->file_arr = (char **) ft_calloc((d->y_file + 1), sizeof(char *));
		if (!d->file_arr)
		{
			close (*fd);
			free (*line);
			return (1);
		}
	}
	return (0);
}

int	create_file_array(t_data *d, char *argv)
{
	int		fd;
	int		i;
	char	*line;

	if (setup_file(d, &fd, &line, argv) == 1)
		return (1);
	i = 0;
	while (line && i < d->y_file)
	{
		d->file_arr[i] = (char *) ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!d->file_arr[i])
		{
			while (i > 0)
				free(d->file_arr[--i]);
			free(d->file_arr);
			return (1);
		}
		ft_strlcpy(d->file_arr[i], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	d->file_arr[i] = NULL;
	close(fd);
	return (0);
}

int	get_dimensions_of_file(t_data *d, char *argv)
{
	int		fd;
	char	*line;
	int		max;
	int		count;

	count = 0;
	max = 0;
	if (setup_file(NULL, &fd, &line, argv) == 1)
		return (1);
	max = ft_strlen(line);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
		if ((size_t) max < ft_strlen(line))
			max = ft_strlen(line);
	}
	if (max < 3 || count < 1)
		return (close (fd), 1);
	d->y_file = count;
	d->x_file = max;
	close(fd);
	return (0);
}

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
