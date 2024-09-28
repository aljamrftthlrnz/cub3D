#include "../includes/cub3d.h"

int *parse_rgb_colors(char *str, t_data *d, char *ptr)
{
	char **rgb_values;
	int *rgb; 
	int i;
	int num; 

	i= -1;
	if(check_multiple_seperators(str))
	{
		free(ptr);
		ptr = NULL;
		err_free_message(d, FL_CEIL_M);
	}
	rgb_values = ft_split(str, ',');
	if(!rgb_values)
	{
		free (ptr);
		ptr = NULL;
		err_free_message(d, ALLOC_FAIL);
	}
	num = file_length(rgb_values);
	if(num > 3)
	{
		free_array(rgb_values);
		free(ptr);
		rgb_values = NULL;
		ptr = NULL;
		err_free_message(d, FL_CEIL_M);
	}
	rgb = (int*)malloc(sizeof(int)*3); 
	if (rgb == NULL)
	{
		free_array(rgb_values);
		rgb_values = NULL;
		free(ptr);
		ptr = NULL;
		err_free_message(d, ALLOC_FAIL);
	}
	while(++i < 3)
	{
		rgb[i] = ft_atoi(rgb_values[i]);
		if(rgb[i] < 0 || rgb[i] > 255)
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
	// free(ptr);
	return (rgb); 
}

char	*parse_texture(t_data *d, char *trim)
{
	char *path;
	int	i;

	i = 0;
	path = ft_strdup(trim + 3);
	if (path ==  NULL)
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

void textures_comp(char*trim, t_data *d, int *err, int *map)
{
	if(!is_map_line(trim))
		(*map)++;
	else if(!ft_strncmp(trim, "NO ", 3))
	{
		if(d->elem->no_path != NULL)
		{
			free (trim); 
			err_free_message(d, PERS_D); 
		}
		d->elem->no_path = parse_texture(d, trim);
	}
	else if(!ft_strncmp(trim, "SO ", 3))
	{
		if(d->elem->so_path != NULL)
		{
			free (trim); 
			err_free_message(d, PERS_D);
		}
		d->elem->so_path = parse_texture(d, trim);
	}
	else if(!ft_strncmp(trim, "WE ", 3))
	{
		if(d->elem->we_path != NULL)
		{
			free (trim); 
			err_free_message(d, PERS_D);
		}
		d->elem->we_path = parse_texture(d, trim);
	}
	else if(!ft_strncmp(trim, "EA ", 3))
	{
		if(d->elem->ea_path != NULL)
		{
			free (trim); 
			err_free_message(d, PERS_D);
		}
		d->elem->ea_path = parse_texture(d, trim);
	}
	else if(!ft_strncmp(trim, "F ", 2))
	{
		if(d->elem->flo_rgb != NULL)
		{
			free (trim); 
			err_free_message(d, FL_CEIL_D);
		}
		d->elem->flo_rgb = parse_rgb_colors(trim + 2, d, trim); 
	}
	else if(!ft_strncmp(trim, "C ", 2))
	{
		if(d->elem->ceil_rgb != NULL)
		{
			free (trim); 
			err_free_message(d, FL_CEIL_D);
		}
		d->elem->ceil_rgb = parse_rgb_colors(trim + 2, d, trim);
	}
	else 
		(*err)++;
}

int extract_textures(t_data *d, char **arr)
{
   int i;
   int err;
   int map;
   char *trim;

   i = 0;
   err = 0;
   map = 0;
   trim = NULL;
   if(!arr)
		return (1);
	while(arr[i])
	{
		if(!arr[i])
			break ;
		if(arr[i] && !is_space(arr[i]))
		{
			//printf("is space\n");
			i++; 
			continue ;   
		}
		else 
		{
			//printf("is not space \n");
			trim = ft_strtrim(arr[i], " ");
			if(trim == NULL || trim[0] == '\0')
			{
				//printf("NOW-----------\n");    
				return (free(trim), 1);
			}
			//printf("Trimmed -%s-\n", trim); 
			textures_comp(trim, d, &err, &map);
			free (trim);  
			trim = NULL;  
			i++;
		}        
	}
	if(err)
	   err_free_message(d, FILE_EMPTY); 
	if(!map)
		err_free_message(d, MISSING_MAP);
	return (0);
}

/*
	//printf("map lines ___ %d\n", map);
	//printf("error counter ___ %d\n", err); 

	printf("Texture SO\n%s\n", d->elem->so_path);
	printf("Texture WE\n%s\n", d->elem->we_path);
	printf("Texture EA\n%s\n", d->elem->ea_path);
	printf("Texture NO\n%s\n", d->elem->no_path);
	printf("COLOR CEILING\n%d|%d|%d\n", d->elem->flo_rgb[0], d->elem->flo_rgb[1], d->elem->flo_rgb[2]);
	printf("COLOR FLOOR\n%d|%d|%d\n", d->elem->ceil_rgb[0], d->elem->ceil_rgb[1], d->elem->ceil_rgb[2])
*/
