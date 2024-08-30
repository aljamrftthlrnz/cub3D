#include "../includes/cub3d.h"

int assign_direction_and_camera_plane(t_raycast *r, t_map *map)
{
    int i;
    int j;

    if(!r || !map)
        return (1); 
    i = map->pos_y;
    j = map->pos_x;
    r->p_pos_x = j; 
    r->p_pos_y = i; 
    if(map->map[i][j] && map->map[i][j] == 'N')
    {
        r->dir_x = 0; 
        r->dir_y = -1;
        r->plane_x = 0.66; 
        r->plane_y = 0;
    }
    else if(map->map[i][j] && map->map[i][j] == 'S')
    {
        r->dir_x = 0; 
        r->dir_y = 1;
        r->plane_x = -0.66; 
        r->plane_y = 0;
    }
    else if(map->map[i][j] && map->map[i][j] == 'W')
    {
        r->dir_x = -1; 
        r->dir_y = 0;
        r->plane_x = 0;
        r->plane_y = -0.66; 
    }
    else if(map->map[i][j] && map->map[i][j] == 'E')
    {
        r->dir_x = 1; 
        r->dir_y = 0;
        r->plane_x = 0;
        r->plane_y = 0.66;
    }
    return (0);
}

void loop_through_colum_on_screen(t_map *map, t_raycast *r)
{
    int x;
    x = 0; 
    while(x < screenWidth)
    {
        r->camera_x = 2 * x / (double)screenWidth - 1;
        printf("Camera_x %f \n", r->camera_x); 
        r->rayDirX = r->dir_x + r->plane_x * r->camera_x;
        r->rayDirY = r->dir_y + r->plane_y * r->camera_x;
        calc_playerposition_and_stepvalues(r);
        ray_hits_wall(map, r);
        x++;
    }
}

int calc_playerposition_and_stepvalues(t_raycast *r)
{
    
    r->mapX = (int)r->p_pos_x;
    r->mapY = (int)r->p_pos_y;
    printf("Map x [%d] und map y [%d]\n", r->mapX,r->mapY ); 

    r->deltaDistX = fabs(1/r->rayDirX);
    r->deltaDistY = fabs(1/r->rayDirY);
    if(r->rayDirX < 0)
    {
        r->stepX = -1;
        r->sideDistX = (r->p_pos_x - r->mapX) * r->deltaDistX;
    }
    else 
    {
        r->stepX = 1;
        r->sideDistX = (r->mapX + 1.0 - r->p_pos_x) * r->deltaDistX; 
    }
    if(r->rayDirY < 0)
    {
        r->stepY = -1; 
        r->sideDistY = (r->p_pos_y - r->mapY) * r->deltaDistY; 
    }
    else 
    {
        r->stepY = 1; 
        r->sideDistY = (r->mapY + 1.0 -r->p_pos_y) * r->deltaDistY;
    }
    return (0); 
}

void determine_distance_to_wall(t_raycast *ray, int side)
{
    if(side == 0)
        ray->perpWallDist = (ray->mapX - ray->p_pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
    else 
        ray->perpWallDist = (ray->mapY - ray->p_pos_y + (1 - ray->stepY) / 2) / ray->rayDirY; 
}

int ray_hits_wall(t_map *map, t_raycast *ray)
{
    int hit = 0;
    int side = 0; 
    printf("HELLO");
    printf("Side dir x __ [%f]\n and y[%f]\n", ray->sideDistX, ray->sideDistY); 
    while (!hit)
    {
        if(ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX; 
            ray->mapX += ray->stepX;
            side = 0; 
        }
        else
        {
            ray->sideDistY += ray->deltaDistY; 
            ray->mapY += ray->stepY;
            side = 1;
        }
        if(map->cpy_map[ray->mapX][ray->mapY] == '1')
            printf("HELLO"); 
    }
    return (0); 
}

void init_raycasting(t_data *d)
{
    t_raycast *ray;
    t_map *map;

    ray = d->file->ray;
    map = d->file->map;
    if(assign_direction_and_camera_plane(ray, map))
        err_free_message(d, 0);
    loop_through_colum_on_screen(map, ray);
}