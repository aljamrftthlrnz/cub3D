/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:52:53 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:52:54 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' \
		|| c == 'S' || c == 'W' || c == 'E' || c == '\n')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!is_space(line))
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_map_char(line[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	calc_map_size(t_data *d, int begin)
{
	int	size;
	int	i;

	i = file_length(d->file_arr) - 1;
	while (d->file_arr[i] && !is_space(d->file_arr[i]))
		i--;
	size = i - begin;
	return (size);
}

char	**copy_map_parts_in_file(t_data *d, int bg)
{
	char	**map;
	int		j;
	int		map_size;

	j = 0;
	map_size = calc_map_size(d, bg) + 1;
	map = (char **) ft_calloc(map_size + 1, sizeof(char *));
	if (!map)
		return (NULL);
	while (j < map_size)
	{
		map[j] = (char *) ft_calloc(ft_strlen(d->file_arr[bg]) + 1, \
			sizeof(char));
		if (!map[j])
		{
			free_array(map);
			return (NULL);
		}
		ft_strlcpy(map[j], d->file_arr[bg], ft_strlen(d->file_arr[bg]) + 1);
		j++;
		bg++;
	}
	map[j] = NULL;
	return (map);
}

int	process_map(t_data *d)
{
	int		i;
	int		begin;
	int		res;
	char	**arr;

	i = 0;
	begin = 0;
	arr = d->file_arr;
	while (arr[i] != NULL)
	{
		res = is_map_line(arr[i]);
		if (res == 0)
			break ;
		i++;
	}
	if (arr[i] == NULL)
		return (1);
	begin = i;
	d->map->map = copy_map_parts_in_file(d, begin);
	if (d->map->map == NULL)
		return (1);
	return (0);
}
