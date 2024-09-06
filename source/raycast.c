#include "../includes/cub3d.h"

void init_north_south(t_game *g, t_raycast *r)
{
    if (g->p_pos_dir == DIR_N)  // Use the passed 'dir' parameter instead of global 'g'
    {
        g->dir_x = 0; 
        g->dir_y = -1;
        r->plane_x = 0.66; 
        r->plane_y = 0;
    }
    else if (g->p_pos_dir == DIR_S)
    {
        g->dir_x = 0; 
        g->dir_y = 1;
        r->plane_x = -0.66; 
        r->plane_y = 0;
    }
}

void init_east_west(t_game *g, t_raycast *r)
{
    if(g->p_pos_dir == DIR_W)
    {
        g->dir_x = -1; 
        g->dir_y = 0;
        r->plane_x = 0;
        r->plane_y = -0.66; 
    }
    else if(g->p_pos_dir == DIR_E)
    {
        g->dir_x = 1; 
        g->dir_y = 0;
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
        init_north_south(g,r);
    else 
        init_east_west(g,r);
}

void position_and_stepvalues(t_game *g, t_raycast *r)
{
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
}


void determine_distance_to_wall(t_raycast *ray, t_game *game)
{
    if(ray->side == 0)
        ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else 
        ray->perpWallDist = (ray->sideDistY - ray->deltaDistY); 
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
        }
    }
}

void vertical_line_height(t_element *e, t_raycast *ray, t_game *g)
{
    e->line_height = (int)(screenHeight / ray->perpWallDist);
    e->drawStart = -(e->line_height) / 2 + screenHeight / 2;
    if(e->drawStart < 0)
        e->drawStart = 0;
    e->drawEnd = e->line_height / 2 + screenHeight / 2;
    if(e->drawEnd >= screenHeight)
        e->drawEnd = screenHeight - 1;
    if(ray->side == 0)
        e->wallx = g->pos_y + ray->perpWallDist * ray->rayDirY;
    else 
        e->wallx = g->pos_x + ray->perpWallDist * ray->rayDirX;
    e->wallx -= floor(e->wallx);  // get the fractional part by substracting the integer part
}



void init_loop(int x, t_raycast *r, t_game *g)
{
    r->camera_x = 2 * x / (double)screenWidth - 1;
    //printf("Camera_x %f \n", r->camera_x);
    r->rayDirX = r->dir_x + r->plane_x * r->camera_x;
    r->rayDirY = r->dir_y + r->plane_y * r->camera_x;
    r->mapX = (int)g->pos_x;
    r->mapY = (int)g->pos_y;
    if(r->rayDirX == 0)
        r->deltaDistX = 1e30;
    else
        r->deltaDistX = fabs(1/r->rayDirX);
    if(r->rayDirY == 0)
        r->deltaDistY = 1e30; 
    else 
        r->deltaDistY = fabs(1/r->rayDirY);

}

void decide_map_texture(t_raycast *r, t_element *e)
{
    if(r->side == 0)
    {
        if(r->rayDirX > 0)
            e->texnum = EAST; // East texture
        else 
            e->texnum = WEST; // West texture
    }
    else
    {
        if(r->rayDirY > 0)
            e->texnum = SOUTH; // South texture
        else 
            e->texnum = NORTH; // North texture
    }

}

void handle_texture_update(t_raycast *r, t_element *e)
{
    int y;
    int colour; 

    y = 0; 
    decide_map_texture(r, e);
    e->texx = (int)(e->wallx *(double)e->width); 
    if(r->side == 0 && r->rayDirX > 0)
        e->texx = e->width - e->texx - 1;
    if(r->side == 1 && r->rayDirY < 0)
        e->texx = e->width - e->texx -1;
    e->step = 1.0 * e->height / e->line_height;
    e->texpos = (e->drawStart - screenHeight / 2 + e->line_height / 2) * e->step; 
    y = e->drawStart;
    while(y < e->drawEnd)
    {
        e->texy = (int)e->texpos & (e->height - 1); 
        e->texpos += e->step; 
        
        y++;
    }
}

void ray_loop(t_game *g, t_raycast *r, t_map *m, t_element *e)
{
    int x;

    x = 0;
    while(x < screenWidth)
    {
        init_loop(x, r, g); 
        position_and_stepvalues(g, r);
        wall_hit(m, r);
        determine_distance_to_wall(r, g);
        //printf("Distance to wall %f\n", r->perpWallDist);
        vertical_line_height(e, r, g);
        handle_texture_update(e); 


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
            {
               printf("OLD: %c\n", c);
               m->map[i][j] = '0';
               printf("NEW: %c\n", m->map[i][j]); 

            }
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
    t_element   *e;

    g = d->game; 
    ray = d->ray;
    map = d->map;
    e = d->elem;
    init_ray(ray,map,g);
    replace_initial_player_pos(map); 
    ray_loop(g, ray, map, e);
    printf("DONE\n"); 
}