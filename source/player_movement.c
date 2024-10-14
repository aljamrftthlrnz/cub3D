#include "../includes/cub3d.h"

// void	arrow_keys(t_data *d, int keycode)
// {

// 	t_raycast *r = d->ray; 
// 	t_game *g = d->game; 
// 	double oldDirX;
// 	double oldPlaneX;
	
// 	if(keycode == KEY_RIGHT)
// 	{
// 		oldDirX = g->dir_x; 
// 		g->dir_x = g->dir_x * cos(r->rot_speed) - g->dir_y * sin(r->rot_speed); 
// 		g->dir_y = oldDirX * sin (r->rot_speed) + g->dir_y * cos(r->rot_speed); 
// 		oldPlaneX = r->plane_x; 
// 		r->plane_x = r->plane_x * cos(r->rot_speed) - r->plane_y * sin (r->rot_speed);
// 		r->plane_y = oldPlaneX * sin (r->rot_speed) + r->plane_y * cos(r->rot_speed);
// 	}
// 	if (keycode == KEY_LEFT)
// 	{
// 		oldDirX = g->dir_x; 
// 		g->dir_x = g->dir_x * cos(-r->rot_speed) - g->dir_y * sin(-r->rot_speed); 
// 		g->dir_y = oldDirX * sin (-r->rot_speed) + g->dir_y * cos(-r->rot_speed); 
// 		oldPlaneX = r->plane_x; 
// 		r->plane_x = r->plane_x * cos(-r->rot_speed) - r->plane_y * sin (-r->rot_speed);
// 		r->plane_y = oldPlaneX * sin (-r->rot_speed) + r->plane_y * cos(-r->rot_speed);
// 	}
// }

// void	player_step(t_data *d, int keycode)
// {
// 	t_map *m = d->map;
// 	t_game *g = d->game; 
// 	t_raycast *r = d->ray;

//     if (keycode == KEY_W)
//     {
// 		if(m->cpy_map[(int)(g->pos_y + g->dir_y * (r->moveSpeed + 0.1))][(int)(g->pos_x + g->dir_x * (r->moveSpeed + 0.1))] != '1')
// 		{
// 			d->game->pos_x += d->game->dir_x * r->moveSpeed;
//         	d->game->pos_y += d->game->dir_y * r->moveSpeed;
// 		}
//     }
//     if (keycode == KEY_S)
//     {
// 		if(m->cpy_map[(int)(g->pos_y - g->dir_y * (r->moveSpeed + 0.1))][(int)(g->pos_x - g->dir_x * (r->moveSpeed + 0.1))] != '1')
//         {
// 			d->game->pos_x -= d->game->dir_x * r->moveSpeed;
//         	d->game->pos_y -= d->game->dir_y * r->moveSpeed;
// 		}	
//     }
//     if (keycode == KEY_A)
//     {
// 		if(m->cpy_map[(int)(g->pos_y - r->plane_y * (r->moveSpeed + 0.1))][(int)(g->pos_x - r->plane_x * (r->moveSpeed + 0.1))] != '1')
//         {
// 			d->game->pos_x -= d->ray->plane_x * r->moveSpeed;
//         	d->game->pos_y -= d->ray->plane_y * r->moveSpeed;
// 		}
//     }
//     if (keycode == KEY_D)
//     {
// 		if(m->cpy_map[(int)(g->pos_y + r->plane_y * (r->moveSpeed + 0.1))][(int)(g->pos_x + r->plane_x * (r->moveSpeed + 0.1))] != '1')
// 		{
//         	d->game->pos_x += d->ray->plane_x * r->moveSpeed;	
// 			d->game->pos_y += d->ray->plane_y * r->moveSpeed;
// 		}
//     }
// }

void	arrow_keys(t_data *d, int keycode)
{
	double radian_angle;
	double	tmp;

	if (keycode == KEY_LEFT)
	{
		d->game->p_pos_dir -= KEY_ROT_ANGL;
		printf("Rot speed %d\n", d->game->p_pos_dir);
		radian_angle = -KEY_ROT_ANGL * (PI / 180);
	}
	if (keycode == KEY_RIGHT)
	{
		d->game->p_pos_dir += KEY_ROT_ANGL;
		radian_angle = KEY_ROT_ANGL * (PI / 180);
	}
	tmp = d->ray->plane_x;
	d->ray->plane_x = d->ray->plane_x * cos(radian_angle) - d->ray->plane_y * sin(radian_angle);
	d->ray->plane_y = tmp * sin(radian_angle) + d->ray->plane_y * cos(radian_angle);
	tmp = d->game->dir_x;
	d->game->dir_x = d->game->dir_x * cos(radian_angle) - d->game->dir_y * sin(radian_angle);
	d->game->dir_y = tmp * sin(radian_angle) + d->game->dir_y * cos(radian_angle);
	while (d->game->p_pos_dir < 0)
	{
		d->game->p_pos_dir = 360 + d->game->p_pos_dir;
	}
	while (d->game->p_pos_dir > 359)
	{
		d->game->p_pos_dir = d->game->p_pos_dir - 360;
	}
	printf("direction: %d\n", d->game->p_pos_dir); //debugging help
}


void	normalize_vector(double *x, double *y)
{
	double  magnitude;

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

void	angle_calc(int angle, int keycode, double *p_left, double *p_right)
{
	double	tmp;

	printf("angle: %d\n", angle); //debugging help
	*p_left = (double) angle / 9 / 10;
	*p_right = 1 - *p_left;
	if (keycode == KEY_S)
	{
		*p_left = *p_left * (-1);
		*p_right = *p_right * (-1);
	}
	if (keycode == KEY_A)
	{
		tmp = *p_left;
		*p_left = *p_right  * (-1);
		*p_right = tmp;
	}
	if (keycode == KEY_D)
	{
		tmp = *p_left;
		*p_left = *p_right;
		*p_right = tmp * (-1);
	}
	normalize_vector(p_left, p_right);
	printf("px: %f | py: %f\n", *p_left, *p_right); //debugging help
}

void	player_step(t_data *d, int keycode)
{
	double	p_left;
	double	p_right;
	t_map *m = d->map; 

	angle_calc(d->game->p_pos_dir % 90, keycode, &p_left, &p_right);
	if (d->game->p_pos_dir < 90)
	{
		if(m->cpy_map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x + p_left * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(m->cpy_map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ))][(int)(d->game->pos_x + p_left * (KEY_STP_SIZ))] != '1')
			{

				d->game->pos_x += p_left * KEY_STP_SIZ;
				d->game->pos_y -= p_right * KEY_STP_SIZ;
				d->ray->activate = 1;
				printf("pos_x: %f | pos_y: %f\n", d->game->pos_x, d->game->pos_y); //debugging help
			}
		}
	}
	else if (d->game->p_pos_dir < 180)
	{
		if(m->cpy_map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x + p_right * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(m->cpy_map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ))][(int)(d->game->pos_x + p_right * (KEY_STP_SIZ))] != '1')
			{

				d->game->pos_x += p_right * KEY_STP_SIZ;
				d->game->pos_y += p_left * KEY_STP_SIZ;
				printf("pos_x: %f | pos_y: %f\n", d->game->pos_x, d->game->pos_y); //debugging help
				d->ray->activate = 1;
			}
		}
	}
	else if (d->game->p_pos_dir < 270)
	{
		if(m->cpy_map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x - p_left * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(m->cpy_map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ))][(int)(d->game->pos_x - p_left * (KEY_STP_SIZ))] != '1')
			{

				d->game->pos_x -= p_left * KEY_STP_SIZ;
				d->game->pos_y += p_right * KEY_STP_SIZ;
				printf("pos_x: %f | pos_y: %f\n", d->game->pos_x, d->game->pos_y); //debugging help
				d->ray->activate = 1;
			}
		}
	}
	else if (d->game->p_pos_dir < 360)
	{
		if(m->cpy_map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x - p_right * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(m->cpy_map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ))][(int)(d->game->pos_x - p_right * (KEY_STP_SIZ))] != '1')
			{

				d->game->pos_x -= p_right * KEY_STP_SIZ;
				d->game->pos_y -= p_left * KEY_STP_SIZ;
				printf("pos_x: %f | pos_y: %f\n", d->game->pos_x, d->game->pos_y); //debugging help
				d->ray->activate = 1;
			}
		}	
	}
}




