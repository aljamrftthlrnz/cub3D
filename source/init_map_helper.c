#include "../includes/cub3d.h"

int	is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			return (1);
		}
		i++;
	}
	return (0); 
}

int	is_character(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1); 
	return (0); 
}

int	is_wall_space(char c)
{
	if (c == '0' || c == '1')
		return (1);
	return (0);
}

int	file_length(char **arr)
{
	int	i; 

	i = 0; 
	while (arr[i] != NULL)
		i++; 
	return (i); 
}

int	map_len(char **arr)
{
	int	i;

	i = 0;
	while (is_map_line(arr[i]))
	{
		i++;
	}
	return (i);
}
