
#include "../includes/cub3d.h"

void init_data(t_data *d)
{
	ft_bzero(d, sizeof(t_data));
	d->file = (t_file*)malloc(sizeof(t_file)); 
	if(!d->file)
	{
		d->error = ALLOC_FAIL; 
		return ; 
	}
	ft_bzero(d->file, sizeof(t_data));
	d->file->d = d; 
	d->file->e = (t_element *)malloc(sizeof(t_element)); 
	if(!d->file->e)
	{
		d->error = ALLOC_FAIL; 
		return(free(d->file));
	}
	ft_bzero(d->file->e, sizeof(t_element)); 
	d->file->e->f = d->file; 
	d->file->e->stat = NON; 
	d->file->m =(t_map*)malloc(sizeof(t_map)); 
	if(!d->file->m)
	{
		d->error = 1; 
		return(free(d->file->e), free (d->file)); 
	}
	ft_bzero(d->file->m, sizeof(t_map)); 
	d->file->m->f = d->file; 
	d->file->m->stat = NOM; 
}
