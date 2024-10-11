#include "../includes/cub3d.h"

void vertical_line_height(t_element *e, t_raycast *ray, t_game *g)
{
	//printf("Distance zur Wand ____ %f\n", ray->perpWallDist);
	//e->line_height = (int)(SCREEN_H / avoid_zero_at_all_costs(ray->perpWallDist));
	e->line_height = (int)(SCREEN_H / ray->perpWallDist);
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

void determine_distance_to_wall(t_raycast *ray, t_game *game)
{
	if(ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else 
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY); 
	(void) game;

	// if (ray->side == 0) {
    // 	ray->perpWallDist = (ray->mapX - game->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
	// } else {
    // 	ray->perpWallDist = (ray->mapY - game->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;
	// }
	// if (ray->perpWallDist < 0.200)
	// 	ray->perpWallDist = 0.200; 
}

void wall_hit(t_map *map, t_raycast *ray)
{
	int loop;

	loop = 0;
	//&& loop < 50)
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
		if (ray->mapX < 0 || ray->mapX >= map->width || ray->mapY < 0 || ray->mapY >= map->length) //avoid segfault
		{
			return ;
		}
		if(map->map[ray->mapY][ray->mapX] == '1') // used to segfault
		{
			ray->hit = 1; 
		}

		//loop++;
	}
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
//printf("Camera_x %f \n", r->camera_x);

void init_loop(int x, t_raycast *r, t_game *g)
{
	r->camera_x = 2 * x / (double) SCREEN_W - 1;
	r->rayDirX = g->dir_x + r->plane_x * r->camera_x;
	r->rayDirY = g->dir_y + r->plane_y * r->camera_x;
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

void ray_loop(t_game *g, t_raycast *r, t_map *m, t_element *e, t_data *d)
{
	int x;
	x = 0;
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