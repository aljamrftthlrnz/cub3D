#include "../includes/cub3d.h"

void init_data(t_data *d)
{
	ft_bzero(d, sizeof(t_data));
	d->file = (t_file*)malloc(sizeof(t_file)); 
	if (!d->file)
		err_free_message (d, ALLOC_FAIL); 
	ft_bzero(d->file, sizeof(t_file));
	d->file->data = d; 
	d->file->elem = (t_element *)malloc(sizeof(t_element)); 
	if (!d->file->elem)
		err_free_message (d, ALLOC_FAIL);
	ft_bzero(d->file->elem, sizeof(t_element)); 
	d->file->elem->file = d->file; 
	d->file->map =(t_map*)malloc(sizeof(t_map)); 
	if(!d->file->map)
		err_free_message(d, ALLOC_FAIL);
	ft_bzero (d->file->map, sizeof(t_map)); 
	d->file->map->file = d->file; 
}
