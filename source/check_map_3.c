/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:52:35 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:52:36 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	line_down(char *map, char *prev)
{
	int	j;

	j = 1;
	while (map[(ft_strlen(prev) - 1) + j])
	{
		if (map[(ft_strlen(prev) - 1) + j] == '0')
			return (1);
		j++;
	}
	return (0);
}

int	line_up(char *map, char *prev)
{
	int	j;

	j = 1;
	while (prev[(ft_strlen(map) - 1) + j])
	{
		if (prev[(ft_strlen(map) - 1) + j] == '0')
		{
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_up_down_left_right(char **map, int i, int j)
{
	if (is_character(map[i][j]) && map[i + 1][j] == '1' && map[i - 1][j] == '1'\
		&& map[i][j + 1] == '1' && map[i][j - 1] == '1')
	{
		return (1);
	}
	if (map[i + 1][j] == 'X' || map[i - 1][j] == 'X' || map[i][j + 1] == 'X'\
		|| map[i][j - 1] == 'X')
	{
		return (1);
	}
	return (0);
}
