#include "../includes/cub3d.h"

void	flood_alloc(t_data *d, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->flood_map = (char **) ft_calloc(sizeof(char *), map->length + 1);
	if (map->flood_map == NULL)
		err_free_message(d, ALLOC_FAIL);
	while (i < map->length)
	{
		map->flood_map[i] = (char *) ft_calloc(sizeof(char), map->width + 1);
		if (map->flood_map[i] == NULL)
			err_free_message(d, ALLOC_FAIL);
		while (j < map->width - 1)
		{
			map->flood_map[i][j] = '.';
			j++;
		}
		j = 0;
		i++;
	}
}

int	print_matrix(char **matrix, int nl)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i], 1);
		if (nl == 1)
			ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

int	char_condition(char c, char f)
{
	if (c == 0 || c == ' ' || c == '\n')
		return (1);
	if (f == '.')
		return (0);
	return (1);
}
