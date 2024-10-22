#include "../includes/cub3d.h"

// send path to use texture and make img the size of texture
// send NULL as path to create image in standard screen size
void	setup_img(t_data *d, t_image *new_img, char *path)
{
	if (path)
		new_img->img_ptr = mlx_xpm_file_to_image(d->mlx, path, \
			&new_img->width, &new_img->height);
	else
	{
		new_img->img_ptr = mlx_new_image(d->mlx, SCREEN_W, SCREEN_H);
		new_img->width = SCREEN_W;
		new_img->height = SCREEN_H;
	}
	if (new_img->img_ptr == NULL)
	{
		free_mlx(d);
		err_free_message(d, MLXIMG);
	}
	new_img->img_adr = mlx_get_data_addr(new_img->img_ptr, \
		&new_img->bits_per_pixel, &new_img->size_line, &new_img->endian);
}

void	check_img_size(t_data *d)
{
	if (d->nesw[0].height != 64 || d->nesw[0].width != 64)
	{
		free_mlx(d);
		err_free_message(d, 103);
	}
	if (d->nesw[1].height != 64 || d->nesw[0].width != 64)
	{
		free_mlx(d);
		err_free_message(d, 103);
	}
	if (d->nesw[2].height != 64 || d->nesw[0].width != 64)
	{
		free_mlx(d);
		err_free_message(d, 103);
	}
	if (d->nesw[3].height != 64 || d->nesw[0].width != 64)
	{
		free_mlx(d);
		err_free_message(d, 103);
	}
}

void	init_img(t_data *d)
{
	d->nesw = (t_image *) ft_calloc(sizeof(t_image), 4);
	d->screen = (t_image *) ft_calloc(sizeof(t_image), 1);
	if (d->nesw == NULL || d->screen == NULL)
	{
		err_free_message(d, ALLOC_FAIL);
	}
	setup_img(d, &d->nesw[0], d->elem->no_path);
	setup_img(d, &d->nesw[1], d->elem->ea_path);
	setup_img(d, &d->nesw[2], d->elem->so_path);
	setup_img(d, &d->nesw[3], d->elem->we_path);
	setup_img(d, d->screen, NULL);
	check_img_size(d);
}
