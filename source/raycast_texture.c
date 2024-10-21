#include "../includes/cub3d.h"

void	decide_map_texture(t_raycast *r, t_element *e)
{
	if (r->side == 0)
	{
		if (r->rayDirX > 0)
			e->texnum = EAST;
		else
		{
			e->texnum = WEST;
			e->wallx = 1 - e->wallx;
		}
	}
	else
	{
		if (r->rayDirY > 0)
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
	if (r->side == 0 && r->rayDirX > 0)
		e->texx = e->width - e->texx - 1;
	if (r->side == 1 && r->rayDirY < 0)
		e->texx = e->width - e->texx -1;
	e->step = 1.0 * e->height / e->line_height;
	e->texpos = (e->drawStart - SCREEN_H / 2 + e->line_height / 2) * e->step;
	y = e->drawStart;
	while (y < e->drawEnd)
	{
		e->texy = (int)e->texpos & (e->height - 1);
		e->texpos += e->step;
		y++;
	}
}

void	vertical_line_height(t_element *e, t_raycast *ray, t_game *g)
{
	e->line_height = (int)(SCREEN_H / ray->perpWallDist);
	e->drawStart = -(e->line_height) / 2 + SCREEN_H / 2;
	if (e->drawStart < 0)
		e->drawStart = 0;
	e->drawEnd = e->line_height / 2 + SCREEN_H / 2;
	if (e->drawEnd >= SCREEN_H)
		e->drawEnd = SCREEN_H - 1;
	if (ray->side == 0)
		e->wallx = g->pos_y + ray->perpWallDist * ray->rayDirY;
	else
		e->wallx = g->pos_x + ray->perpWallDist * ray->rayDirX;
	e->wallx -= floor(e->wallx);
}
