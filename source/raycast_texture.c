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

// Obsolet only keep decide_map_texture
void	handle_texture_update(t_raycast *r, t_element *e)
{
	int	y;

	y = 0;
	decide_map_texture(r, e);
	e->texx = (int)(e->wallx *(double)e->width);
	if (r->side == 0 && r->ray_dirx > 0)
		e->texx = e->width - e->texx - 1;
	if (r->side == 1 && r->ray_diry < 0)
		e->texx = e->width - e->texx -1;
	e->step = 1.0 * e->height / e->line_height;
	e->texpos = (e->draw_start - SCREEN_H / 2 + e->line_height / 2) * e->step;
	y = e->draw_start;
	while (y < e->draw_end)
	{
		e->texy = (int)e->texpos & (e->height - 1);
		e->texpos += e->step;
		y++;
	}
}

void	vertical_line_height(t_element *e, t_raycast *ray, t_game *g)
{
	e->line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	e->draw_start = -(e->line_height) / 2 + SCREEN_H / 2;
	if (e->draw_start < 0)
		e->draw_start = 0;
	e->draw_end = e->line_height / 2 + SCREEN_H / 2;
	if (e->draw_end >= SCREEN_H)
		e->draw_end = SCREEN_H - 1;
	if (ray->side == 0)
		e->wallx = g->pos_y + ray->perp_wall_dist * ray->ray_diry;
	else
		e->wallx = g->pos_x + ray->perp_wall_dist * ray->ray_dirx;
	e->wallx -= floor(e->wallx);
}
