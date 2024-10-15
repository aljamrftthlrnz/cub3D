#include "../includes/cub3d.h"

void	arrow_keys(t_data *d, int keycode)
{
	double radian_angle;
	double	tmp;

	if (keycode == KEY_LEFT)
	{
		d->game->p_pos_dir -= KEY_ROT_ANGL;
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
		d->game->p_pos_dir = 360 + d->game->p_pos_dir;
	while (d->game->p_pos_dir > 359)
		d->game->p_pos_dir = d->game->p_pos_dir - 360;
}

void	normalize_vector(double *x, double *y)
{
	double  magnitude;

	magnitude = sqrt(*x * *x + *y * *y);
	if (magnitude == 0)
		return ;
	else if (magnitude != 1)
	{
		*x = *x * (1 / magnitude);
		*y = *y * (1 / magnitude);
		magnitude = sqrt(*x * *x + *y * *y);
	}
}

void	angle_calc(int angle, int keycode, double *p_left, double *p_right)
{
	double	tmp;

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
}

void	do_the_step(t_data *d, double a, double b)
{
	d->game->pos_x += a;
	d->game->pos_y += b;
	d->ray->activate = 1;
}

void	check_step_1(t_data *d, double p_right, double p_left)
{
	double	x_tmp;
	double	y_tmp;
	double	wc;

// third version
/* checks coordinate +1 individually if there is wall ahead, if wall ahead, wallcollision calculation activates */
/* 	if (d->game->p_pos_dir < 0 || d->game->p_pos_dir >= 90)
		return ;
	if (d->map->map[(int) d->game->pos_y - 1][(int) d->game->pos_x] == '0' || d->map->map[(int) d->game->pos_y][(int) d->game->pos_x + 1] == '0')
	{
		do_the_step(d, p_left * KEY_STP_SIZ, p_right * KEY_STP_SIZ * (-1));
		return ;
	} */
	
	
//second version
/* gradually checks from wc (wallcollision distance) is there is any wall detected */
	if (d->game->p_pos_dir < 0 || d->game->p_pos_dir >= 90)
		return ;
	wc = 0.4;
	x_tmp = d->game->pos_x + p_left * (KEY_STP_SIZ + wc);
	y_tmp = d->game->pos_y - p_right * (KEY_STP_SIZ + wc);
	while (wc >= 0 && d->map->map[(int) y_tmp][(int) x_tmp])
	{
		if (d->map->map[(int) y_tmp][(int) x_tmp] == '0')
		{
			wc -= 0.005;
			x_tmp = d->game->pos_x + p_left * (KEY_STP_SIZ + wc);
			y_tmp = d->game->pos_y - p_right * (KEY_STP_SIZ + wc);
		}
		else
			return ;
	}
	if (wc < 0)
	{
		d->game->pos_x += p_left * KEY_STP_SIZ;
		d->game->pos_y -= p_right * KEY_STP_SIZ;
		d->ray->activate = 1;
	}
	
/*  //first version
	if (d->game->p_pos_dir >= 0 && d->game->p_pos_dir < 90)
	{
		if(d->map->cpy_map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x + p_left * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(d->map->cpy_map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ))][(int)(d->game->pos_x + p_left * (KEY_STP_SIZ))] != '1')
			{
				d->game->pos_x += p_left * KEY_STP_SIZ;
				d->game->pos_y -= p_right * KEY_STP_SIZ;
				d->ray->activate = 1;
			}
		}
	} */

}

void	check_step_2(t_data *d, double p_right, double p_left)
{
	if (d->game->p_pos_dir >= 90 && d->game->p_pos_dir < 180)
	{
		if(d->map->cpy_map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x + p_right * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(d->map->cpy_map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ))][(int)(d->game->pos_x + p_right * (KEY_STP_SIZ))] != '1')
			{
				d->game->pos_x += p_right * KEY_STP_SIZ;
				d->game->pos_y += p_left * KEY_STP_SIZ;
				d->ray->activate = 1;
			}
		}
	}
}

void	check_step_3(t_data *d, double p_right, double p_left)
{
	if (d->game->p_pos_dir >= 180 && d->game->p_pos_dir < 270)
	{
		if(d->map->cpy_map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x - p_left * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(d->map->cpy_map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ))][(int)(d->game->pos_x - p_left * (KEY_STP_SIZ))] != '1')
			{
				d->game->pos_x -= p_left * KEY_STP_SIZ;
				d->game->pos_y += p_right * KEY_STP_SIZ;
				d->ray->activate = 1;
			}
		}
	}

}

void	check_step_4(t_data *d, double p_right, double p_left)
{
	if (d->game->p_pos_dir >= 270 && d->game->p_pos_dir < 360)
	{
		if(d->map->cpy_map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ + 0.1))][(int)(d->game->pos_x - p_right * (KEY_STP_SIZ + 0.1))] != '1')
		{
			if(d->map->cpy_map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ))][(int)(d->game->pos_x - p_right * (KEY_STP_SIZ))] != '1')
			{
				d->game->pos_x -= p_right * KEY_STP_SIZ;
				d->game->pos_y -= p_left * KEY_STP_SIZ;
				d->ray->activate = 1;
			}
		}
	}

}

void	player_step(t_data *d, int keycode)
{
	double	p_left;
	double	p_right;

	angle_calc(d->game->p_pos_dir % 90, keycode, &p_left, &p_right);
	check_step_1(d, p_right, p_left);
	check_step_2(d, p_right, p_left);
	check_step_3(d, p_right, p_left);
	check_step_4(d, p_right, p_left);
}
