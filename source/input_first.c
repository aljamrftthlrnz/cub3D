#include "../includes/cub3d.h"

int invisible_file(char *path)
{
	int len;

	len = ft_strlen(path) -1;
	while (path[len] && is_whitespace(path[len]))
		len--; 
	len -= 4;
	if(path[len] && path[len] == '/')
		return (0);
	return (1);
}

int valid_path(char *path)
{
	char			*tmp;
	unsigned int	i;

	tmp = ft_strnstr(path, ".xpm", ft_strlen(path));
	if(!tmp)
		return (0);
	i = 4; 
	if (tmp[i] && is_whitespace(tmp[i]) == 0)
		return (0);
	if(i < ft_strlen(tmp) - 1)
	{
		while (tmp[i] != '\0')
		{
			if(!is_whitespace(tmp[i]))
				return (0);
			i++; 
		}
	}
	return (1);
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
	if (!invisible_file(path) || !valid_path(path))
	{
		free (trim); 
		free(path);
		err_free_message(d, TXT_WRONG);
	}
	return (modify_path(path));
}

// returns 0 for success
int	is_identifier(t_data *d, void **path, char *id, char *trim)
{
	if (!ft_strncmp(trim, id, ft_strlen(id)))
	{
		if (*path != NULL)
		{
			free (trim);
			if (ft_strlen(id) > 2)
				err_free_message(d, PERS_D);
			else
				err_free_message(d, FL_CEIL_D);
		}
		if (ft_strlen(id) > 2)
		{
			*path = parse_texture(d, trim);
		}
		else
			*path = parse_rgb_colors(trim + 2, d, trim);
		return (0);
	}
	return (1);
}

void	textures_comp(char *trim, t_data *d, int *map)
{
	if (!is_map_line(trim))
		(*map)++;
	else if (is_identifier(d, (void **) &d->elem->no_path, "NO ", trim) == 0)
		return ;
	else if (is_identifier(d, (void **) &d->elem->so_path, "SO ", trim) == 0)
		return ;
	else if (is_identifier(d, (void **) &d->elem->we_path, "WE ", trim) == 0)
		return ;
	else if (is_identifier(d, (void **) &d->elem->ea_path, "EA ", trim) == 0)
		return ;
	else if (is_identifier(d, (void **) &d->elem->flo_rgb, "F ", trim) == 0)
		return ;
	else if (is_identifier(d, (void **) &d->elem->ceil_rgb, "C ", trim) == 0)
		return ;
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
