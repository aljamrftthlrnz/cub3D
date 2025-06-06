/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:52:42 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:52:43 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**create_map_copy(t_map *map)
{
	char	**s;
	int		size;
	int		i;

	i = 0;
	size = file_length(map->map);
	s = (char **) malloc(sizeof(char *) * (size + 1));
	if (s == NULL)
		return (NULL);
	while (i < size)
	{
		s[i] = (char *) malloc(sizeof(char) * (ft_strlen(map->map[i]) + 1));
		if (!s[i])
		{
			free_array(s);
			return (NULL);
		}
		ft_strlcpy(s[i], map->map[i], ft_strlen(map->map[i]));
		i++;
	}
	s[i] = NULL;
	return (s);
}

void	get_player_direction_position(int y, int x, t_map *m)
{
	m->pos_x = x;
	m->pos_y = y;
	if (m->cpy_map[y][x] == 'N')
		m->p_pos_dir = DIR_N;
	else if (m->cpy_map[y][x] == 'S')
		m->p_pos_dir = DIR_S;
	else if (m->cpy_map[y][x] == 'W')
		m->p_pos_dir = DIR_W;
	else if (m->cpy_map[y][x] == 'E')
		m->p_pos_dir = DIR_E;
	else
		return ;
}

int	replace_spaces_and_check_player(t_map *map, char **s)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (i < (file_length(s)))
	{
		j = 0;
		while ((size_t)j < (ft_strlen(s[i]) + 1))
		{
			if (s[i][j] && s[i][j] == ' ')
				s[i][j] = 'X';
			else if (s[i][j] && is_character(s[i][j]) && p++ >= 0)
				get_player_direction_position (i, j, map);
			else if (s[i][j] && !is_valid_map_char(s[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (p != 1)
		return (1);
	return (0);
}

int	check_empty_lines_in_map(t_map *m)
{
	int		i;
	char	**map;

	i = 0;
	map = m->map;
	while (map[i] != NULL)
	{
		if (!is_space(map[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	map_related_checks(t_data *d, t_map *map)
{
	if (check_empty_lines_in_map(map))
		err_free_message(d, EMPTY_LINES);
	map->cpy_map = create_map_copy(map);
	if (!map->cpy_map)
		err_free_message(d, ALLOC_FAIL);
	if (replace_spaces_and_check_player(map, map->cpy_map))
		err_free_message(d, PLAYER_W);
	if (validating_map_walls(map->cpy_map))
		err_free_message(d, BORDER_M);
	if (check_for_free_zeros(map->cpy_map))
		err_free_message(d, SPACE_PROT);
	if (validating_map_content(map->cpy_map))
		err_free_message(d, SPACE_PROT);
}
