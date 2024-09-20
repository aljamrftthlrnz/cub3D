#include "../includes/cub3d.h"


void element(t_element *e) 
{
    e->no_path = NULL;
    e->so_path = NULL;
    e->we_path = NULL; 
    e->ea_path = NULL; 
    e->ceil_rgb = NULL; 
    e->flo_rgb = NULL;
    e->texnum = -1;
    e->texx = 0;
    e->width = texSize; 
    e->height = texSize;
    e->wallx = 0; 
}

void map(t_map *map) 
{
    map->cpy_map = NULL;
    map->map = NULL;
    map->length = 0;
    map->width = 0; 
}

void raycast(t_raycast *ray)
{
    ray->rotation_speed = 0;
    rotation(ray); 
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
    ray->hit = 0;
    ray->side = 0;
}

void game(t_game *g)
{
    g->pos_x = 0; 
    g->pos_y = 0;
    g->dir_x = 0; 
    g->dir_y = 0;
    g->p_pos_dir = -1; 
}

void data(t_data *d) 
{
    d->file_arr = NULL;
    d->mlx = NULL;
    d->win = NULL;
    d->error = 0;
    d->x_file = 0;
    d->y_file = 0;
}



void rotation(t_raycast *r)
{
    float radians_per_second; 

    radians_per_second = (DEGREES * PI) / 180.0;
    r->rotation_speed = radians_per_second / FPS; 
}

void init_data(t_data *d) 
{
    data(d);
    d->elem = (t_element*)malloc(sizeof(t_element)); 
    if(!d->elem)
        err_free_message(d, ALLOC_FAIL);
    element(d->elem);
    d->map = (t_map*)malloc(sizeof(t_map)); 
    if(!d->map)
        err_free_message(d, ALLOC_FAIL);
    map(d->map);
    d->ray = (t_raycast*)malloc(sizeof(t_raycast));
    if(!d->ray)
        err_free_message(d, ALLOC_FAIL);
    raycast(d->ray);
    d->game = (t_game*)malloc(sizeof(t_game));
    if(!d->game)
        err_free_message(d, ALLOC_FAIL);
    game(d->game); 
     d->game_l = (t_game_luca *) malloc(sizeof(t_game_luca));
    if (d->game_l == NULL)
        err_free_message(d, ALLOC_FAIL);
    return ; 
}


