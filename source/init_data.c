#include "../includes/cub3d.h"

void data(t_data *d) {
    // Zero out the entire structure first
    ft_bzero(d, sizeof(t_data));

    // Explicitly set fields, if needed (optional after zeroing out)
    d->error = 0;
    d->file_arr = NULL;
    d->mlx = NULL;
    d->win = NULL;
    d->x_file = 0;
    d->y_file = 0;
}

void element(t_element *e) {
    // Zero out the entire structure first
    ft_bzero(e, sizeof(t_element));

    // Explicitly set fields, if needed
    e->no_path = NULL;
    e->so_path = NULL;
    e->we_path = NULL; 
    e->ea_path = NULL; 
    e->ceil_rgb = NULL; 
    e->flo_rgb = NULL;
}

void map(t_map *map) {
    // Zero out the entire structure first
    ft_bzero(map, sizeof(t_map));

    // Explicitly set fields, if needed
    map->cpy_map = NULL;
    map->map = NULL;
    map->length = 0;
    map->width = 0; 
}

void raycast(t_raycast *ray)
{
    ft_bzero(ray, sizeof(t_raycast));
    ray->p_pos_x = 0;
    ray->p_pos_y = 0;
    ray->dir_x = 0; 
    ray->dir_y = 0;
    ray->plane_x = 0; 
    ray->plane_y = 0; 
    ray->camera_x = 0;
    ray->camera_y = 0;
    ray->rayDirX = 0;
    ray->rayDirY = 0;
    ray->deltaDistX = 0;
    ray->deltaDistY = 0;
    ray->sideDistX = 0;
    ray->sideDistY = 0;
    ray->stepX = 0;
    ray->stepY = 0;
    ray->mapX = 0;
    ray->mapY = 0;
    ray->perpWallDist = 0; 


}

void init_data(t_data *d) 
{
    data(d);
    d->file = (t_file*)malloc(sizeof(t_file)); 
    if (!d->file)
        err_free_message(d, ALLOC_FAIL);
    ft_bzero(d->file, sizeof(t_file));
    d->file->data = d; 
    
    d->file->elem = (t_element *)malloc(sizeof(t_element)); 
    if (!d->file->elem)
        err_free_message(d, ALLOC_FAIL);
    element(d->file->elem);
    d->file->elem->file = d->file; 
    
    d->file->map = (t_map*)malloc(sizeof(t_map)); 
    if (!d->file->map)
        err_free_message(d, ALLOC_FAIL);
    map(d->file->map);
    d->file->map->file = d->file;
    
    d->file->ray = (t_raycast*)malloc(sizeof(t_raycast));
    if(!d->file->ray)
       err_free_message(d, ALLOC_FAIL); 
    raycast(d->file->ray);
    d->file->ray->file = d->file;
}


