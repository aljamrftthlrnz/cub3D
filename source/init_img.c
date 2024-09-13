#include "../includes/cub3d.h"

void init_img(t_data *d)
{
	int	img_size;

	d->NESW = (t_image *) ft_calloc(sizeof(t_image), 4);
	if (d->NESW == NULL)
	{
		err_free_message(d, ALLOC_FAIL);
	}

	d->NESW[0].img_ptr = mlx_xpm_file_to_image(d->mlx, d->file->elem->no_path , &img_size, &img_size);
	d->NESW[1].img_ptr = mlx_xpm_file_to_image(d->mlx, d->file->elem->ea_path, &img_size, &img_size);
	d->NESW[2].img_ptr = mlx_xpm_file_to_image(d->mlx, d->file->elem->so_path, &img_size, &img_size);
	d->NESW[3].img_ptr = mlx_xpm_file_to_image(d->mlx, d->file->elem->we_path, &img_size, &img_size);
}