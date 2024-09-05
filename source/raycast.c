#include "../includes/cub3d.h"

void init_north_south(int dir, t_raycast *r)
{
    if (dir == DIR_N)  // Use the passed 'dir' parameter instead of global 'g'
    {
        r->dir_x = 0; 
        r->dir_y = -1;
        r->plane_x = 0.66; 
        r->plane_y = 0;
    }
    else if (dir == DIR_S)
    {
        r->dir_x = 0; 
        r->dir_y = 1;
        r->plane_x = -0.66; 
        r->plane_y = 0;
    }
}

void init_east_west(int dir, t_raycast *r)
{
    if(dir == DIR_W)
    {
        r->dir_x = -1; 
        r->dir_y = 0;
        r->plane_x = 0;
        r->plane_y = -0.66; 
    }
    else if(dir == DIR_E)
    {
        r->dir_x = 1; 
        r->dir_y = 0;
        r->plane_x = 0;
        r->plane_y = 0.66;
    }
}

void init_ray(t_raycast *r, t_map *map, t_game *g)
{
    g->p_pos_dir = map->p_pos_dir;
    g->pos_x = map->pos_x;
    g->pos_y = map->pos_y;
    if(g->p_pos_dir == DIR_N || g->p_pos_dir == DIR_S)
        init_north_south(g->p_pos_dir,r);
    else 
        init_east_west(g->p_pos_dir,r);
}



void position_and_stepvalues(t_game *g, t_raycast *r)
{
    r->mapX = (int)g->pos_x;
    r->mapY = (int)g->pos_y;
    printf("Map x [%d] und map y [%d]\n", r->mapX, r->mapY ); 
    r->deltaDistX = fabs(1/r->rayDirX);
    r->deltaDistY = fabs(1/r->rayDirY);
    if(r->rayDirX < 0)
    {
        r->stepX = -1;
        r->sideDistX = (g->pos_x - r->mapX) * r->deltaDistX;
    }
    else 
    {
        r->stepX = 1;
        r->sideDistX = (r->mapX + 1.0 - g->pos_x) * r->deltaDistX; 
    }
    if(r->rayDirY < 0)
    {
        r->stepY = -1; 
        r->sideDistY = (g->pos_y - r->mapY) * r->deltaDistY; 
    }
    else 
    {
        r->stepY = 1; 
        r->sideDistY = (r->mapY + 1.0 - g->pos_y) * r->deltaDistY;
    }
    printf("Side dir x __ [%f]\n and y[%f]\n", r->sideDistX, r->sideDistY); 
}


void determine_distance_to_wall(t_raycast *ray, t_game *game)
{
    if(ray->side == 0)
        ray->perpWallDist = (ray->mapX - game->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
    else 
        ray->perpWallDist = (ray->mapY - game->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY; 
}

void wall_hit(t_map *map, t_raycast *ray)
{
    while (!ray->hit)
    {
        if(ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX; 
            ray->mapX += ray->stepX;
            ray->side = 0; 
        }
        else
        {
            ray->sideDistY += ray->deltaDistY; 
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if(map->map[ray->mapY][ray->mapX] == '1')
        {
            ray->hit = 1; 
            printf("HELLO"); 
        }
    }
}

void ray_loop(t_game *g, t_raycast *r, t_map *m)
{
    int x;

    x = 0;
    while(x < screenWidth)
    {
        r->camera_x = 2 * x / (double)screenWidth - 1;
        printf("Camera_x %f \n", r->camera_x); 
        r->rayDirX = r->dir_x + r->plane_x * r->camera_x;
        r->rayDirY = r->dir_y + r->plane_y * r->camera_x;
        position_and_stepvalues(g, r);
        wall_hit(m, r);
        determine_distance_to_wall(r, g);  
        x++;



    /*while (game_loop)
    {
        // Player auf map ersetzen
        // assign player direction
        // assign player position
        // camera_x | raydirX | raydirY
        // mapX | mapY 
        // deltaDistX | deltaDistY
        // stepX and stepY || sideDistX and sideDistY
        // see which side was hit and when is wall from position of player
        // calculate distance to the wall hit        


    }
    */
    }
}
void replace_initial_player_pos(t_map *m)
{
    char    c;
    int     i;
    int     j;

    i = 0; 
    c = m->map[m->pos_y][m->pos_x];
    while(m->map[i] != NULL)
    {
        j = 0;
        while(m->map[i][j] != '\0')
        {
            if(m->map[i][j] == c)
                m->map[i][j] = '0';
            j++; 
        }
        i++;
    }
}

void raycasting(t_data *d)
{
    t_raycast   *ray;
    t_map       *map;
    t_game      *g;

    g = d->game; 
    ray = d->ray;
    map = d->map;

    init_ray(ray,map,g);
    replace_initial_player_pos(map); 
    ray_loop(g, ray, map);
    printf("DONE\n"); 
}