#include "../includes/cub3d.h"

int check_multiple_seperators(char *str)
{
	int sep;
	int i;

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

int check_order_of_map(t_data *d)
{
	int length;
	int j; 

	length = file_length(d->file_arr); 
	j = length - 1; 
	while(!is_space(d->file_arr[j]))
		j--; 
	if(is_map_line(d->file_arr[j]))
		return(1); 
	return (0); 
}

int order(char *trim, int *sum)
{
	if(!ft_strncmp(trim, "NO ", 3))
		*sum = 1; 
	else if(!ft_strncmp(trim, "SO ", 3) && *sum == 1)
		*sum = 2; 
	else if(!ft_strncmp(trim, "WE ", 3) && *sum == 2)
		*sum = 3; 
	else if(!ft_strncmp(trim, "EA ", 3) && *sum == 3)
		*sum = 4; 
	else if(!ft_strncmp(trim, "F ", 2) && *sum == 4)
		*sum = 5; 
	else if(!ft_strncmp(trim, "C ", 2) && *sum == 5) 
		*sum = 6;
	else if(is_map_line(trim))
		*sum = *sum;
	return (0);
}

int check_order_of_file(t_data *d)
{
	char **arr;
	char *s;
	int i;
	int sum;

	arr = d->file_arr;
	i = 0;
	sum = 0; 
	while(arr[i])
	{
		if(!is_space(arr[i]) || !is_map_line(arr[i]))
		{
			i++; 
			continue ; 
		}
		else
		{
			s = ft_strtrim(arr[i], " ");
			//printf("line is ___ %s\n", s); 
			order(s, &sum);
			//printf("sum is ___ %d\n", sum); 
			free (s);
			i++; 
		}
	}
	return (sum); 
}