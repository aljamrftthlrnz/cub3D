#include "../includes/cub3d.h"

char **create_map_copy(t_map *map)
{
	char **s; 
	int size;
	int i;
	
	i = 0;
	size = file_length(map->map);
	s = (char **)malloc(sizeof(char*)*(size+1)); 
	while(i < size)
	{
		s[i] = (char*)malloc(sizeof(char)*(ft_strlen(map->map[i])+1));
		if(!s[i])
		{
			while(i >= 0)
			{
				free(s[i]); 
				i--;
			}
			return(free(s), NULL);
		}
		ft_strlcpy(s[i], map->map[i], ft_strlen(map->map[i])); 
		i++;
	}
	s[i] = NULL; 
	return (s); 
}

void    get_player_direction_position(int y, int x, t_map *m)
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

int replace_spaces_and_check_player(t_map *map, char **s)
{
   int i;
   int j;
   int p;
   int err;

   i = 0;
   p = 0; 
   err = 0;
   while(i < (file_length(s)))
   {
		j = 0;
		while ((size_t)j < (ft_strlen(s[i]) + 1))
		{
			if(s[i][j] && s[i][j] == ' ')
				s[i][j] = 'X';
			else if (s[i][j] && is_character(s[i][j]))
			{
				p++;
				get_player_direction_position (i, j, map); 
			}
			else if (s[i][j] && !is_valid_map_char(s[i][j]))
				err++;
			j++; 
		}
		i++; 
	}
	if (p != 1 || err != 0)
		return(1);
	return(0); 
}

int check_empty_lines_in_map(t_map *m)
{
	int i;
	char **map;

	i = 0;
	map = m->map; 
	while(map[i] != NULL)
	{
		if(!is_space(map[i]))
		{
			printf("Wrong line %s\n", map[i]); 
			return (1); 
		}
		i++;
	}
	return (0); 
}

int loop_over_potential_walls(char *s)
{
	int i;
	int x; 

	i = 0;
	x = 0;
	while(s[i])
	{
		if(s[i] && s[i] == '1')
		{
			if(x)
				x = 0;
		}
		else if (s[i] && s[i] == 'X')
			x++;
		else 
			return (1); 
		i++;
	}
	if(x)
		return (1); 
	return (0);
}

int validate_outer_walls(char *cpy)
{
	int i;

	i = 0;
	if(!cpy)
		return(1); 
	while(cpy[i] && cpy[i] == 'X')
		i++;
	if(cpy[i] && cpy[i] == '1' && cpy[ft_strlen(cpy)-1] == '1')
		return (0);
	return (1);
}

int validating_map_walls(char **cpy)
{
	int i;
	int size; 

	i = -1;
	size = file_length(cpy);
	while(++i < size)
	{
		if(i == 0 || i == (size - 1))
		{
			if(loop_over_potential_walls(cpy[i]))
				return (1); 
		}
		else
		{
			if(validate_outer_walls(cpy[i]))
				return (1);
		}
	}
	return (0);

}

void map_related_checks(t_data *data, t_map *map)
{
	if(check_empty_lines_in_map(map))
		err_free_message(data, EMPTY_LINES);
	map->cpy_map = create_map_copy(map);
	if(!map->cpy_map)
		err_free_message(data, ALLOC_FAIL);
	if(replace_spaces_and_check_player(map, map->cpy_map))
		err_free_message(data, PLAYER_W);
	if(validating_map_walls(map->cpy_map))
		err_free_message(data, BORDER_M);
	if(validating_map_content(map->cpy_map))
		err_free_message(data, SPACE_PROT);
}

int validating_map_content(char **s)
{
	int i;
	int j;
	char *prev;

	i = 0;
	prev = NULL;
	while(s[i] != NULL && i < (file_length(s)-1))
	{
		j = 0;
		prev = s[i];
		while(prev && (size_t)j < (ft_strlen(s[i])+1))
		{
			if(s[i][j] && (s[i][j] == '0' || is_character(s[i][j])))
			{
				if(check_up_down_left_right(s, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int check_up_down_left_right(char **map, int i, int j)
{
	if(is_character(map[i][j]) && map[i+1][j] == '1' && map[i-1][j] == '1' && map[i][j+1] == '1'  && map[i][j-1] == '1')
	{
		return (1); 
	}
	if(map[i+1][j] == 'X' || map[i-1][j] == 'X'|| map[i][j+1] == 'X'|| map[i][j-1] == 'X')
	{
		return (1);
	}
	return (0);
}
