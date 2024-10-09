#include "../includes/cub3d.h"


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
	if(cpy[i] && cpy[i] == '1' && (cpy[ft_strlen(cpy)-1] == '1' || cpy[ft_strlen(cpy)-1] == 'X'))
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
			{
				printf("line _________ %s\n", cpy[i]); 	
				return (1); 
			}
		}
		else
		{
			if(validate_outer_walls(cpy[i]))
			{
				printf("line (2) _________ %s\n", cpy[i]); 	
				return (1);
			}
		}
	}
	return (0);
}
