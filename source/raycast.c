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

void test (t_data *d)
{
    t_raycast *r = d->file->ray;
    float rayDirX = r->dir_x; 
    float rayDirY = r->dir_y;
    
// How far to the next X or Y boundary in the grid

// The distance the ray has to travel to go from one x-side to the next x-side

 


// Calculate stepX and stepY based on the direction of the ray
   
// Check every step the ray takes to see if it hits a wall;
   
    float perpWallDist;
    if(side == 0)
        perpWallDist = (mapX - r->p_pos_x + (1 - stepX) / 2 ) / rayDirX;
    else 
        perpWallDist = (mapY - r->p_pos_y + (1 - stepY) / 2 ) / rayDirY;
// Calculate the wall height when ray hits wall
    int line_height; 
    line_height = (int)(screenHeight / perpWallDist);
// calculate start and end points of the wall
    int drawStart =-line_height / 2 + screenHeight / 2;
    if (drawStart < 0)
        drawStart = 0; 
    int drawEnd = line_height / 2 + screenHeight / 2; 
    if (drawEnd >= screenHeight)
        drawEnd = screenHeight - 1;
// For each raycast, you'll render a vertical line at the appropriate height
}

int loop_through_colum_on_screen(t_raycast *r)
{
    int x;
    x = 0; 

    while(x < screenWidth)
    {
        r->camera_x = 2 * x / (float)screenWidth - 1;
        r->rayDirX = r->dir_x + r->plane_x * r->camera_x;
        r->rayDirY = r->dir_y + r->plane_y * r->camera_x;
        x++;
    }
}

int calc_playerposition_and_stepvalues(t_raycast *r)
{
    r->mapX = (int)r->p_pos_x;
    r->mapY = (int)r->p_pos_y;
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
    ray_hits_wall(r);  
    return (0); 
}

void determine_distance_to_wall(t_raycast *ray, int side)
{
    if(side == 0)
        ray->perpWallDist = (ray->mapX - ray->p_pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
    else 
        ray->perpWallDist = (ray->mapY - ray->p_pos_y + (1 - ray->stepY) / 2) / ray->rayDirY; 
}

int ray_hits_wall(t_raycast *ray)
{
    int hit = 0;
    int side; 

    while (hit == 0)
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
        if(ray->file->map->map[ray->mapX][ray->mapY] > 0)
            hit = 1;
    }
    if (hit)
        determine_distance_to_wall(ray, side); 

}

void init_raycasting(t_data *d)
{
    t_raycast *ray;
    t_map *map;

    ray = d->file->ray;
    map = d->file->map;
    if(assign_direction_and_camera_plane(ray, map))
        err_free_message(d, 0);
	printf("Dir X ___ %f\nDir Y ___ %f\n", ray->dir_x, ray->dir_y); 
    if(loop_through_colum_on_screen(ray))
        err_free_message(d, 1); 
    if(calc_playerposition_and_stepvalues(ray))
        err_free_message(d, 2);
    if(ray_hits_wall(ray))
        err_free_message(d, 3);
    //test(d); 

}