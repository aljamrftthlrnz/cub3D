#include "../includes/cub3d.h"

void	decide_map_texture(t_raycast *r, t_element *e)
{
	if (r->side == 0)
	{
		if (r->ray_dirx > 0)
			e->texnum = EAST;
		else
		{
			e->texnum = WEST;
			e->wallx = 1 - e->wallx;
		}
	}
	else
	{
		if (r->ray_diry > 0)
		{
			e->texnum = SOUTH;
			e->wallx = 1 - e->wallx;
		}
		else
			e->texnum = NORTH;
	}
}

void	vertical_line_height(t_element *e, t_raycast *ray, t_game *g)
{
	e->line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	e->draw_end = e->line_height / 2 + SCREEN_H / 2;
	if (e->draw_end >= SCREEN_H)
		e->draw_end = SCREEN_H - 1;
	if (ray->side == 0)
		e->wallx = g->pos_y + ray->perp_wall_dist * ray->ray_diry;
	else
		e->wallx = g->pos_x + ray->perp_wall_dist * ray->ray_dirx;
	e->wallx -= floor(e->wallx);
}
