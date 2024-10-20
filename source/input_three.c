#include "../includes/cub3d.h"

void	rgb_null_check(t_data *d, char **rgb_values, int *rgb, char *ptr)
{
	if (!rgb_values || !rgb || file_length(rgb_values) != 3)
	{
		free (ptr);
		if (!rgb_values || !rgb)
		{
			free(rgb);
			free_array(rgb_values);
			err_free_message(d, ALLOC_FAIL);
		}
		free(rgb);
		free_array(rgb_values);
		err_free_message(d, FL_CEIL_M);
	}
}

int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		else if (str[i] == '\n' && str[i + 1] == '\0')
			break ;
		else if (ft_isalpha(str[i]) || !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	spaces_between_numerals(char *value)
{
	int	i;

	i = 0;
	if (!value || value[i] == '\0')
		return (0);
	while (value[i] && value[i] == ' ')
		i++;
	while (value[i] && ft_isdigit(value[i]))
		i++;
	while (value[i] && (value[i] == ' ' || value[i] == '\n'))
		i++;
	if (value[i] != '\0')
		return (0);
	return (1);
}

int	is_valid_rgb(char *value)
{
	if (!is_digit_str(value) || !is_space(value) || \
		!spaces_between_numerals(value))
	{
		return (0);
	}
	return (1);
}

char	**setup_rgb_values(t_data *d, char *str, char *ptr)
{
	if (check_multiple_seperators(str))
	{
		free(ptr);
		err_free_message(d, FL_CEIL_M);
	}
	return (ft_split(str, ','));
}
