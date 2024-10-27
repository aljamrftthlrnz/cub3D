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

int	char_condition(char c, char f)
{
	if (c == 0 || c == ' ' || c == '\n')
		return (1);
	if (f == '.')
		return (0);
	return (1);
}
