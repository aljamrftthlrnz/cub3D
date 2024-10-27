/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:53:32 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:53:33 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
