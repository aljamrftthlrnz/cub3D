#include	"../includes/cub3d.h"

void	free_data(t_data *d)
{
	if(d != NULL)
	{
		if(d->file != NULL)
		{
			if(d->file->map != NULL)
			{
				// free_array(d->file->map->cpy_map); 
				// free_array(d->file->map->map); 
				free(d->file->map); 
			}
			if (d->file->elem != NULL)
			{
				if (d->file->elem->we_path != NULL)
					free(d->file->elem->we_path); 
				if (d->file->elem->no_path != NULL)
					free(d->file->elem->no_path); 
				if(d->file->elem->so_path != NULL)
					free(d->file->elem->so_path);
				if(d->file->elem->ea_path != NULL)
					free(d->file->elem->ea_path);
				if(d->file->elem->flo_rgb != NULL)
					free(d->file->elem->flo_rgb);
				if(d->file->elem->ceil_rgb != NULL)
					free(d->file->elem->ceil_rgb);
				free(d->file->elem); 
			}
			free(d->file); 
		}
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
