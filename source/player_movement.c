#include "../includes/cub3d.h"

void	arrow_keys(t_data *d, int keycode)
{

	t_raycast *r = d->ray; 
	t_game *g = d->game; 
	double oldDirX;
	double oldPlaneX;
	
	if(keycode == KEY_RIGHT)
	{
		oldDirX = g->dir_x; 
		g->dir_x = g->dir_x * cos(r->rot_speed) - g->dir_y * sin(r->rot_speed); 
		g->dir_y = oldDirX * sin (r->rot_speed) + g->dir_y * cos(r->rot_speed); 
		oldPlaneX = r->plane_x; 
		r->plane_x = r->plane_x * cos(r->rot_speed) - r->plane_y * sin (r->rot_speed);
		r->plane_y = oldPlaneX * sin (r->rot_speed) + r->plane_y * cos(r->rot_speed);
	}
	if (keycode == KEY_LEFT)
	{
		oldDirX = g->dir_x; 
		g->dir_x = g->dir_x * cos(-r->rot_speed) - g->dir_y * sin(-r->rot_speed); 
		g->dir_y = oldDirX * sin (-r->rot_speed) + g->dir_y * cos(-r->rot_speed); 
		oldPlaneX = r->plane_x; 
		r->plane_x = r->plane_x * cos(-r->rot_speed) - r->plane_y * sin (-r->rot_speed);
		r->plane_y = oldPlaneX * sin (-r->rot_speed) + r->plane_y * cos(-r->rot_speed);
	}
}

void	player_step(t_data *d, int keycode)
{
	t_map *m = d->map;
	t_game *g = d->game; 
	t_raycast *r = d->ray;

    if (keycode == KEY_W)
    {
		if(m->cpy_map[(int)(g->pos_y + g->dir_y * r->moveSpeed)][(int)(g->pos_x + g->dir_x * r->moveSpeed)] != '1')
		{
			d->game->pos_x += d->game->dir_x * r->moveSpeed;
        	d->game->pos_y += d->game->dir_y * r->moveSpeed;
		}
    }
    if (keycode == KEY_S)
    {
		if(m->cpy_map[(int)(g->pos_y - g->dir_y * r->moveSpeed)][(int)(g->pos_x - g->dir_x * r->moveSpeed)] != '1')
        {
			d->game->pos_x -= d->game->dir_x * r->moveSpeed;
        	d->game->pos_y -= d->game->dir_y * r->moveSpeed;
		}	
    }
    if (keycode == KEY_A)
    {
		if(m->cpy_map[(int)(g->pos_y - r->plane_y * r->moveSpeed)][(int)(g->pos_x - r->plane_x * r->moveSpeed)] != '1')
        {
			d->game->pos_x -= d->ray->plane_x * r->moveSpeed;
        	d->game->pos_y -= d->ray->plane_y * r->moveSpeed;
		}

    }
    if (keycode == KEY_D)
    {
		if(m->cpy_map[(int)(g->pos_y + r->plane_y * r->moveSpeed)][(int)(g->pos_x + r->plane_x * r->moveSpeed)] != '1')
		{
        	d->game->pos_x += d->ray->plane_x * r->moveSpeed;	
			d->game->pos_y += d->ray->plane_y * r->moveSpeed;

		}
    }
}



