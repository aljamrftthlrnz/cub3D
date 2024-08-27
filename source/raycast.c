#include "../includes/cub3d.h"

int assign_initial_direction(t_raycast *r, t_map *map)
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
    }
    else if(map->map[i][j] && map->map[i][j] == 'S')
    {
        r->dir_x = 0; 
        r->dir_y = 1;
    }
    else if(map->map[i][j] && map->map[i][j] == 'W')
    {
        r->dir_x = -1; 
        r->dir_y = 0;
    }
    else if(map->map[i][j] && map->map[i][j] == 'E')
    {
        r->dir_x = 1; 
        r->dir_y = 0;
    }
    return (0);
}

void test (t_data *d)
{
    t_raycast *r = d->file->ray;
    float rayDirX = r->dir_x; 
    float rayDirY = r->dir_y;
    int mapX = r->p_pos_x;
    int mapY = r->p_pos_y;
// How far to the next X or Y boundary in the grid
    float sideDistX;
    float sideDistY;
// The distance the ray has to travel to go from one x-side to the next x-side
    float deltaDistX = fabs(1/rayDirX);
    float deltaDistY = fabs(1/rayDirY);

    int stepX;
    int stepY;

// Calculate stepX and stepY based on the direction of the ray
    if(rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (r->p_pos_x - mapX) * deltaDistX;
    }
    else 
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - r->p_pos_x) * deltaDistX; 
    }
    if(rayDirY < 0)
    {
        stepY = -1; 
        sideDistY = (r->p_pos_y - mapY) * deltaDistY; 
    }
    else 
    {
        stepY = 1; 
        sideDistY = (mapY + 1.0 -r->p_pos_y) * deltaDistY;
    }
// Check every step the ray takes to see if it hits a wall;
    int hit = 0;
    int side; 

    while (hit == 0)
    {
        if(sideDistX < sideDistY)
        {
            sideDistX += deltaDistX; 
            mapX += stepX;
            side = 0; 
        }
        else
        {
            sideDistY += deltaDistY; 
            mapY += stepY;
            side = 1;
        }
        if(d->file->map->cpy_map[mapX][mapY] > 0)
            hit = 1; 
    }

}




void init_raycasting(t_data *d)
{
    t_raycast *ray;
    t_map *map;

    ray = d->file->ray;
    map = d->file->map;
	if(assign_initial_direction(ray, map))
        err_free_message(d, 0);
    test(d); 

}