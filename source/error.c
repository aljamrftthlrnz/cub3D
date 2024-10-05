#include "../includes/cub3d.h"



void free_element(t_element *e)
{
	if (e->we_path != NULL)
		free(e->we_path); 
	if (e->no_path != NULL)
		free(e->no_path); 
	if(e->so_path != NULL)
		free(e->so_path);
	if(e->ea_path != NULL)
		free(e->ea_path);
	if(e->flo_rgb != NULL)
		free(e->flo_rgb);
	if(e->ceil_rgb != NULL)
		free(e->ceil_rgb);
}

void	free_data(t_data *d)
{
	if(d != NULL)
	{
		if(d->map != NULL)
		{
			free_array(d->map->cpy_map); 
			free_array(d->map->map); 
			free(d->map); 
		}
		if (d->elem != NULL)
		{
			free_element(d->elem);
			free(d->elem); 
		}
		if(d->ray != NULL)
			free(d->ray);
		if(d->game != NULL)
			free(d->game);
		free_array(d->file_arr); 
	}
	d = NULL;
}

void	free_mlx(t_data *d)
{
	if (d->win)
	{
		mlx_destroy_window(d->mlx, d->win);
	}
	if (d->NESW)
	{
		if (d->NESW[0].img_ptr)
			mlx_destroy_image(d->mlx, d->NESW[0].img_ptr);
		if (d->NESW[1].img_ptr)
			mlx_destroy_image(d->mlx, d->NESW[1].img_ptr);
		if (d->NESW[2].img_ptr)
			mlx_destroy_image(d->mlx, d->NESW[2].img_ptr);
		if (d->NESW[3].img_ptr)
			mlx_destroy_image(d->mlx, d->NESW[3].img_ptr);
		free (d->NESW);
	}
	if (d->screen)
	{
		if (d->screen->img_ptr)
			mlx_destroy_image(d->mlx, d->screen->img_ptr);
		free (d->screen);
	}

	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
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

int err_free_message(t_data *d, int error_code)
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
	else if (error_code == MLXSIZ)
		printf("%s", MLXSIZ_M); 
	free_data(d); 
	exit (error_code);  
}
