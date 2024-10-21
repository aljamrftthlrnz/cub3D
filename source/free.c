#include "../includes/cub3d.h"

void	free_exit(char *s1, char *s2)
{
	free (s1);
	free (s2);
}

void	free_element(t_element *e)
{
	if (e->we_path != NULL)
		free(e->we_path);
	if (e->no_path != NULL)
		free(e->no_path);
	if (e->so_path != NULL)
		free(e->so_path);
	if (e->ea_path != NULL)
		free(e->ea_path);
	if (e->flo_rgb != NULL)
		free(e->flo_rgb);
	if (e->ceil_rgb != NULL)
		free(e->ceil_rgb);
}

void	free_data(t_data *d)
{
	if (d != NULL)
	{
		if (d->map != NULL)
		{
			free_array(d->map->cpy_map);
			free_array(d->map->map);
			free_array(d->map->flood_map);
			free(d->map);
		}
		if (d->elem != NULL)
		{
			free_element(d->elem);
			free(d->elem);
		}
		if (d->ray != NULL)
			free(d->ray);
		if (d->game != NULL)
			free(d->game);
		free_array(d->file_arr);
	}
	d = NULL;
}

void	free_mlx(t_data *d)
{
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
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
			arr[i] = NULL;
			i++;
		}
		free(arr);
	}
	arr = NULL;
}
