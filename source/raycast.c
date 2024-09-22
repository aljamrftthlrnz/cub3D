#include "../includes/cub3d.h"



void init_north_south(t_game *g, t_raycast *r)
{
    if (g->p_pos_dir == DIR_N)  // Use the passed 'dir' parameter instead of global 'g'
    {
        g->dir_x = 0; 
        g->dir_y = -1;
        r->plane_x = PLANE; 
        r->plane_y = 0;
    }
    else if (g->p_pos_dir == DIR_S)
    {
        g->dir_x = 0; 
        g->dir_y = 1;
        r->plane_x = -PLANE; 
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
        r->plane_y = -PLANE; 
    }
    else if(g->p_pos_dir == DIR_E)
    {
        g->dir_x = 1; 
        g->dir_y = 0;
        r->plane_x = 0;
        r->plane_y = PLANE;
    }
}

void    normalize_vector(double *x, double *y)
{
    double  magnitude;
    // double   experiment_x;
    // double   experiment_y;

    magnitude = sqrt(*x * *x + *y * *y);
    printf("magnitude is %f\n", magnitude);
    if (magnitude == 0)
        printf("keep thinking...magnitude is zero\n");
    else if (magnitude != 1)
    {
        *x = *x * (1/magnitude);
        *y = *y * (1/magnitude);
        magnitude = sqrt(*x * *x + *y * *y);
        printf("new magnitude is %f x: %f, y: %f\n", magnitude, *x, *y);

    }
    
}

void    translate_angle_to_cube(t_game *g, t_raycast *r)
{
    int angle;

    angle = g->p_pos_dir % 90;
    if (g->p_pos_dir > 270)
    {
        g->dir_x = (double) (angle / 9 / 10) * (-1);
	    g->dir_y = (double)(1 - angle / 9 / 10) * (-1);
        normalize_vector(&g->dir_x, &g->dir_y);
    }
    else if (g->p_pos_dir > 180)
    {
        g->dir_y = (double) angle / 9 / 10;
	    g->dir_x = (double) (1 - (angle / 9 / 10)) * (-1);        
        normalize_vector(&g->dir_x, &g->dir_y);
    }
    else if (g->p_pos_dir > 90)
    {
        g->dir_x = (double) angle / 9 / 10;
	    g->dir_y = (double) 1 - (angle / 9 / 10);        
        normalize_vector(&g->dir_x, &g->dir_y);
    }
    else
    {
        g->dir_y = (double) (angle / 9 / 10) * (-1);
	    g->dir_x = (double) 1 - (angle / 9 / 10);        
        normalize_vector(&g->dir_x, &g->dir_y);
    }

    (void) r;
    // if (g->p_pos_dir > 315 || g->p_pos_dir <= 45)
    // {
    //     r->plane_x = PLANE; 
    //     r->plane_y = 0;
    // }
    // else if (g->p_pos_dir > 225)
    // {
    //     r->plane_x = 0;
    //     r->plane_y = -PLANE;
    // }
    // else if (g->p_pos_dir > 135)
    // {
    //     r->plane_x = -PLANE; 
    //     r->plane_y = 0;
    // }
    // else if (g->p_pos_dir > 45)
    // {
    //     r->plane_x = 0;
    //     r->plane_y = PLANE;
    // }
}


void init_ray(t_raycast *r, t_map *map, t_game *g)
{
    // game struct is already initialized
    // g->p_pos_dir = map->p_pos_dir; 
    // g->pos_x = map->pos_x;
    // g->pos_y = map->pos_y;
    if(g->p_pos_dir == DIR_N || g->p_pos_dir == DIR_S)
        init_north_south(g,r);
    else if (g->p_pos_dir == DIR_E || g->p_pos_dir == DIR_W)
        init_east_west(g,r);
    else
        translate_angle_to_cube(g, r);
    (void) map;
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
    (void) game;
}

void wall_hit(t_map *map, t_raycast *ray)
{
    int loop;

    loop = 0;
    while (!ray->hit && loop < 10)
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
        if (ray->mapX < 0 || ray->mapX >= map->width || ray->mapY < 0 || ray->mapY >= map->length) //avoid segfault
        {
            return ;
        }
        if(map->map[ray->mapY][ray->mapX] == '1') // used to segfault
        {
            ray->hit = 1; 
        }
        loop++;
    }
}

double   avoid_zero_at_all_costs(double definitely_not_zero)
{
    if (definitely_not_zero == 0)
    {
        printf("avoided zero\n");
        return (0.00000000001);
    }
    return (definitely_not_zero);
}


void vertical_line_height(t_element *e, t_raycast *ray, t_game *g)
{
    e->line_height = (int)(SCREEN_H / avoid_zero_at_all_costs(ray->perpWallDist));
    e->drawStart = -(e->line_height) / 2 + SCREEN_H / 2;
    if(e->drawStart < 0)
        e->drawStart = 0;
    e->drawEnd = e->line_height / 2 + SCREEN_H / 2;
    if(e->drawEnd >= SCREEN_H)
        e->drawEnd = SCREEN_H - 1;
    if(ray->side == 0)
        e->wallx = g->pos_y + ray->perpWallDist * ray->rayDirY;
    else 
        e->wallx = g->pos_x + ray->perpWallDist * ray->rayDirX;
    e->wallx -= floor(e->wallx);  // get the fractional part by substracting the integer part
}



void init_loop(int x, t_raycast *r, t_game *g)
{
    r->camera_x = 2 * x / (double) SCREEN_W - 1;
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
    // int colour; 

    y = 0; 
    decide_map_texture(r, e);
    e->texx = (int)(e->wallx *(double)e->width); 
    if(r->side == 0 && r->rayDirX > 0)
        e->texx = e->width - e->texx - 1;
    if(r->side == 1 && r->rayDirY < 0)
        e->texx = e->width - e->texx -1;

    
    e->step = 1.0 * e->height / e->line_height;
    e->texpos = (e->drawStart - SCREEN_H / 2 + e->line_height / 2) * e->step; 
    y = e->drawStart;
    while(y < e->drawEnd)
    {
        e->texy = (int)e->texpos & (e->height - 1); 
        e->texpos += e->step;
        // Uint32 color = texture[texNum][texHeight * texY + texX];
        /*
        if(side == 1) 
            color = (color >> 1) & 8355711;
        buffer[y][x] = color;
        */
        y++;
    }
}

void ray_loop(t_game *g, t_raycast *r, t_map *m, t_element *e, t_data *d)
{
    int x;

    x = 0;
    // while(!done())
    while(x < SCREEN_W)
    {
        init_loop(x, r, g); 
        position_and_stepvalues(g, r);
        wall_hit(m, r);
        if (r->hit == 1)
        {
            determine_distance_to_wall(r, g);
            vertical_line_height(e, r, g);
            handle_texture_update(r, e);
        }
		render_column(d, x);
        r->hit = 0;
        


        x += LINE_W;
    }
}


// purpose is to replace the starting out character NESW with a 0 right? so only needs to be run once
// i moved the function call outside of raycasting into main
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
               break ;

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
    // replace_initial_player_pos(map); 
    ray_loop(g, ray, map, e, d);
    // printf("DONE\n"); 
}