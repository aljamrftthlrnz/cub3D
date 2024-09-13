#include "../includes/cub3d.h"


void	free_mlx(t_data *d)
{
	if (d->win)
	{
		mlx_destroy_window(d->mlx, d->win);
	}
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
}

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
		free (d->game);
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

int err_free_message(t_data *data, int error_code)
{
	printf("Error\n");
	if(error_code == ARG_FAIL)
		printf("%s", ARG);
	else if (error_code == EXT_ERROR)
		printf("%s", EXT); 
	else if (error_code == ALLOC_FAIL)
		printf("%s", ALLOC_F);
	else if (error_code == IDENT_W)
		printf("%s", IDENT);
	else if (error_code == PERS_D)
		printf("%s", PERS);
	else if (error_code == PERS_M)
		printf("%s", PERS_MI);
	else if (error_code == FL_CEIL_M)
		printf("%s", FL_CE_MISS);
	else if (error_code == FL_CEIL_D)
		printf("%s", FLOOR_CEILING);
	else if (error_code == RGB_W)
		printf("%s", RGB_WRO);
	else if (error_code == ORDER)
		printf("%s", ORDER_W);
	else if (error_code == MISSING_MAP)
		printf("%s", MISS_MAP);
	else if (error_code == FILE_EMPTY)
		printf("%s", FILE_EMPT);
	else if (error_code == ORDER_ID)
		printf("%s", ORDER_I);
	else if (error_code == EMPTY_LINES)
		printf("%s", EMPTY_L);
	else if (error_code == BORDER_M)
		printf("%s", BORDER);
	else if (error_code == PLAYER_W)
		printf("%s", PLAYER);
	else if(error_code == SPACE_PROT)
		printf("%s", SPACE); 
	else if (error_code == MLXIN)
		printf("%s", MLXIN_M); 
	else if (error_code == MLXWI)
		printf("%s", MLXWI_M); 
	else if (error_code == MLXIMG)
		printf("%s", MLXIMG_M); 
	free_data(data); 
	exit (error_code);  
}
