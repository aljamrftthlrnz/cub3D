#include "../includes/cub3d.h"


// send path to use texture and make img the size of texture
// send NULL as path to create image in standard screen size
void	setup_img(t_data *d, t_image *new_img, char *path)
{
	if (path)
		new_img->img_ptr = mlx_xpm_file_to_image(d->mlx, path ,&new_img->width, &new_img->height);
	else
		new_img->img_ptr = mlx_new_image(d->mlx, SCREEN_W, SCREEN_H);
	if (new_img->img_ptr == NULL)
	{
		err_free_message(d, MLXIMG);
	}
	new_img->img_adr = mlx_get_data_addr(new_img->img_ptr, &new_img->bits_per_pixel, &new_img->size_line, &new_img->endian);
}

void init_img(t_data *d)
{

	d->NESW = (t_image *) ft_calloc(sizeof(t_image), 4);
	d->screen = (t_image *) ft_calloc(sizeof(t_image), 1);
	if (d->NESW == NULL || d->screen == NULL)
	{
		err_free_message(d, ALLOC_FAIL);
	}
	setup_img(d, &d->NESW[0], d->file->elem->no_path);
	setup_img(d, &d->NESW[1], d->file->elem->ea_path);
	setup_img(d, &d->NESW[2], d->file->elem->so_path);
	setup_img(d, &d->NESW[3], d->file->elem->we_path);
	setup_img(d, d->screen, NULL);
}