#include "../includes/cub3d.h"

int	check_multiple_seperators(char *str)
{
	int	sep;
	int	i;

	i = 0;
	sep = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (sep)
				return (1);
			sep = 1;
		}
		else
			sep = 0;
		i++;
	}
	return (sep);
}

int	check_order_of_map(t_data *d)
{
	int	length;
	int	j;

	length = file_length(d->file_arr);
	j = length - 1;
	while (!is_space(d->file_arr[j]))
		j--;
	if (is_map_line(d->file_arr[j]))
		return (1);
	return (0);
}

int	*parse_rgb_colors(char *str, t_data *d, char *ptr)
{
	char	**rgb_values;
	int		*rgb;

	rgb_values = setup_rgb_values(d, str, ptr);
	rgb = (int *) malloc(sizeof(int) * 3);
	rgb_null_check(d, rgb_values, rgb, ptr);
	if (!is_valid_rgb(rgb_values[0]) || !is_valid_rgb(rgb_values[1]) \
		|| !is_valid_rgb(rgb_values[2]))
	{
		free_array(rgb_values);
		free_exit (rgb, ptr);
		err_free_message(d, RGB_MI);
	}
	rgb[0] = ft_atoi(rgb_values[0]);
	rgb[1] = ft_atoi(rgb_values[1]);
	rgb[2] = ft_atoi(rgb_values[2]);
	free_array(rgb_values);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0 \
		|| rgb[2] > 255)
	{
		free_exit(rgb, ptr);
		err_free_message(d, RGB_W);
	}
	return (rgb);
}

char	*modify_path(char *path)
{
	char			*new_path;
	int				i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(path) - 1;
	new_path = NULL;
	while (path[len] && is_whitespace(path[len]))
		len--;
	if (len != ft_strlen(path) - 1)
		path[len + 1] = 0;
	return (path);
}
