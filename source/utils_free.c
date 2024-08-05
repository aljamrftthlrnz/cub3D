#include	"../includes/cub3d.h"

void	free_data(t_data *d)
{
	if(d != NULL)
	{
		if(d->file != NULL)
		{
			if(d->file->map != NULL)
			{
				free_array(d->file->map->cpy_map); 
				free_array(d->file->map->map); 
				free(d->file->map); 
			}
			if (d->file->elem != NULL)
			{
				if (d->file->elem->string != NULL)
					free(d->file->elem->string); 
				if (d->file->elem->path != NULL)
					free(d->file->elem->path); 
				if(d->file->elem->type)
					free(d->file->elem->type); 
				free(d->file->elem); 
			}
			free(d->file); 
		}
		if(d->file_arr != NULL)
			free_array(d->file_arr); 
		free(d);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			free(arr[i]); 
			i++;
		}
		free(arr);
	}
	arr = NULL;
}
