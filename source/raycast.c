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
		r->plane_x = PLANE * (-1); 
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

void init_raycasting(t_raycast *r, t_map *map, t_game *g)
{
	if(g->p_pos_dir == DIR_N || g->p_pos_dir == DIR_S)
		init_north_south(g,r);
	else if (g->p_pos_dir == DIR_E || g->p_pos_dir == DIR_W)
		init_east_west(g,r);
	(void) map;
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