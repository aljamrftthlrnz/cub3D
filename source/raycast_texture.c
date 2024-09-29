#include "../includes/cub3d.h"

void decide_map_texture(t_raycast *r, t_element *e)
{
	if(r->side == 0)
	{
		if(r->rayDirX > 0)
			e->texnum = EAST; // East texture
		else 
		{
			e->texnum = WEST; // West texture
			e->wallx = 1 - e->wallx;
		}
	}
	else
	{
		if(r->rayDirY > 0)
		{
			e->texnum = SOUTH; // South texture
			e->wallx = 1 - e->wallx;
		}
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
