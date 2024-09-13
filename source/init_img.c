#include "../includes/cub3d.h"

void	setup_texture_img(t_data *d, t_image *new_img, char *path)
{
	new_img->img_ptr = mlx_xpm_file_to_image(d->mlx, path ,&new_img->width, &new_img->height);
	if (new_img->img_ptr == NULL)
	{
		err_free_message(d, MLXIMG);
	}
	new_img->img_adr = mlx_get_data_addr(new_img->img_ptr, &new_img->bits_per_pixel, &new_img->size_line, &new_img->endian);
	// new_img->img_ptr = mlx_new_image(d->mlx, IMG_WIDTH, IMG_HEIGHT);
}

void init_img(t_data *d)
{
	int loop;

	loop = 0;

	d->NESW = (t_image *) ft_calloc(sizeof(t_image), 4);
	if (d->NESW == NULL)
	{
		err_free_message(d, ALLOC_FAIL);
	}
	setup_texture_img(d, &d->NESW[0], d->file->elem->no_path);
	setup_texture_img(d, &d->NESW[1], d->file->elem->ea_path);
	setup_texture_img(d, &d->NESW[2], d->file->elem->so_path);
	setup_texture_img(d, &d->NESW[3], d->file->elem->we_path);
}