#include "../includes/cub3d.h"

/* int *fill_texture(t_data *d, t_element *e, char *path, int dir)
{
	e->texture[dir] = mlx_xpm_file_to_image(d->mlx, path, &e->width, &e->height); 
	if(!e->texture[dir])
		return((void*)0);
	mlx_get_data_addr(e->texture[dir], );

}

void init_texture_images(t_data *d)
{
	t_element *e; 

	e = d->elem;
	e->texture = (int**)ft_calloc(4, sizeof(int*));
	if(!e->texture)
		err_free_message(d, ALLOC_FAIL);
	e->texture[NORTH] = fill_texture(d, e, e->no_path, NORTH); 
	e->texture[SOUTH] = 
	e->texture[EAST] = 
	e->texture[WEST] = 
} */