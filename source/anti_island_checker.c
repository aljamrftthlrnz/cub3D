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

// return 1 for NOT OK
// return 0 for OK
int	floodfill_checker(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || y >= map->length)
		return (1);
	if (x >= (int) ft_strlen(map->map[y]))
		return (1);
	if (char_condition(map->map[y][x], map->flood_map[y][x]) != 0)
		return (1);
	return (0);
}

int	floodfill(t_map *map, int x, int y)
{
	map->flood_map[y][x] = 'x';
	if (floodfill_checker(map, x + 1, y) == 0)
		floodfill(map, x + 1, y);
	if (floodfill_checker(map, x, y + 1) == 0)
		floodfill(map, x, y + 1);
	if (floodfill_checker(map, x - 1, y) == 0)
		floodfill(map, x - 1, y);
	if (floodfill_checker(map, x, y - 1) == 0)
		floodfill(map, x, y - 1);
	if (floodfill_checker(map, x + 1, y - 1) == 0)
		floodfill(map, x + 1, y - 1);
	if (floodfill_checker(map, x - 1, y - 1) == 0)
		floodfill(map, x - 1, y - 1);
	if (floodfill_checker(map, x + 1, y + 1) == 0)
		floodfill(map, x + 1, y + 1);
	if (floodfill_checker(map, x - 1, y + 1) == 0)
		floodfill(map, x - 1, y + 1);
	return (0);
}

void	compare_maps(t_data *d, char **map, char **floodmap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] && floodmap[i])
	{
		while (floodmap[i][j])
		{
			if (!map[i][j] || map[i][j] == '\n')
				break ;
			if (map[i][j] != ' ' && map[i][j] != '\n' && floodmap[i][j] == 'x')
			{
				j++;
			}
			else if (map[i][j] == ' ' && floodmap[i][j] == '.')
				j++;
			else
				err_free_message(d, ISLE);
		}
		j = 0;
		i++;
	}
}

// floodfill the available map including walls (delimited by space)
// compare the floodfillmap to the normal map
void	anti_island_checker(t_data *d, t_map *map)
{
	flood_alloc(d, map);
	print_matrix(map->map, 0);
	floodfill(map, map->pos_x, map->pos_y);
	print_matrix(map->flood_map, 1);
	compare_maps(d, map->map, map->flood_map);
	return ;
}
