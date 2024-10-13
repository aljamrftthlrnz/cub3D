#include "../includes/cub3d.h"

int	*parse_rgb_colors(char *str, t_data *d, char *ptr)
{
	char	**rgb_values;
	int		*rgb;
	int		i;
	int		num;

	i = -1;
	if (check_multiple_seperators(str))
	{
		free(ptr);
		ptr = NULL;
		err_free_message(d, FL_CEIL_M);
	}
	rgb_values = ft_split(str, ',');
	if (!rgb_values)
	{
		free (ptr);
		ptr = NULL;
		err_free_message(d, ALLOC_FAIL);
	}
	num = file_length(rgb_values);
	if (num > 3)
	{
		free_array(rgb_values);
		free(ptr);
		rgb_values = NULL;
		ptr = NULL;
		err_free_message(d, FL_CEIL_M);
	}
	rgb = (int *) malloc(sizeof(int) * 3); 
	if (rgb == NULL)
	{
		free_array(rgb_values);
		rgb_values = NULL;
		free(ptr);
		ptr = NULL;
		err_free_message(d, ALLOC_FAIL);
	}
	while (++i < 3)
	{
		rgb[i] = ft_atoi(rgb_values[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free(rgb);
			rgb = NULL;
			free_array(rgb_values);
			rgb_values = NULL;
			free(ptr);
			ptr = NULL;
			err_free_message(d, RGB_W); 
		}
	}
	free_array(rgb_values);
	return (rgb); 
}

char	*parse_texture(t_data *d, char *trim)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup(trim + 3);
	if (path == NULL)
	{
		free (trim);
		err_free_message(d, ALLOC_FAIL);
	}
	while (path && path[i])
	{
		if (path[i] == '\n')
			path[i] = 0;
		i++;
	}
	return (path);
}

// returns 0 for success
int	is_direction(t_data *d, char **path, char *dir, char *trim)
{
	if (!ft_strncmp(trim, dir, 3))
	{
		if (*path != NULL)
		{
			free (trim); 
			err_free_message(d, PERS_D); 
		}
		*path = parse_texture(d, trim);
		return (0);
	}
	return (1);
}


void	textures_comp(char *trim, t_data *d, int *map)
{
	if (!is_map_line(trim))
		(*map)++;
	else if (is_direction(d, &d->elem->no_path, "NO ", trim) == 0)
		return ;
	else if (is_direction(d, &d->elem->so_path, "SO ", trim) == 0)
		return ;
	else if (is_direction(d, &d->elem->we_path, "WE ", trim) == 0)
		return ;
	else if (is_direction(d, &d->elem->ea_path, "EA ", trim) == 0)
		return ;
	else if (!ft_strncmp(trim, "F ", 2))
	{
		if (d->elem->flo_rgb != NULL)
		{
			free (trim); 
			err_free_message(d, FL_CEIL_D);
		}
		d->elem->flo_rgb = parse_rgb_colors(trim + 2, d, trim); 
	}
	else if (!ft_strncmp(trim, "C ", 2))
	{
		if (d->elem->ceil_rgb != NULL)
		{
			free (trim); 
			err_free_message(d, FL_CEIL_D);
		}
		d->elem->ceil_rgb = parse_rgb_colors(trim + 2, d, trim);
	}
	else
	{
		free (trim);
		err_free_message(d, FILE_EMPTY);
	}
}

int	extract_textures(t_data *d, char **arr)
{
	int		i;
	int		map;
	char	*trim;

	i = 0;
	map = 0;
	while (arr && arr[i])
	{
		if (!arr[i])
			break ;
		if (arr[i] && !is_space(arr[i]) && i++ >= 0)
			continue ;
		else
		{
			trim = ft_strtrim(arr[i], " ");
			if (trim == NULL || trim[0] == '\0')
				return (free(trim), 1);
			textures_comp(trim, d, &map);
			free (trim);
			i++;
		}
	}
	if (map == 0)
		err_free_message(d, MISSING_MAP);
	return (0);
}
