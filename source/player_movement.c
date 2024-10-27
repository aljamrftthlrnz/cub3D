/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:54 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:54:55 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// px and py are player position
// cx and cy are center/corner position

// if result of point calc is smaller than r (radius)
	// then player is inside corner radius -> no move possible return 1

void	check_step_1(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 0 && d->game->p_pos_dir < 90))
		return ;
	if (d->map->map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ + 0.1))] \
		[(int)(d->game->pos_x + p_left * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y - p_right * (KEY_STP_SIZ), \
			d->game->pos_x + p_left * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if (d->map->map[(int)(d->game->pos_y - p_right * (KEY_STP_SIZ))] \
			[(int)(d->game->pos_x + p_left * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x += p_left * KEY_STP_SIZ;
			d->game->pos_y -= p_right * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	check_step_2(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 90 && d->game->p_pos_dir < 180))
		return ;
	if (d->map->map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ + 0.1))] \
		[(int)(d->game->pos_x + p_right * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y + p_left * (KEY_STP_SIZ), \
			d->game->pos_x + p_right * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if (d->map->map[(int)(d->game->pos_y + p_left * (KEY_STP_SIZ))] \
			[(int)(d->game->pos_x + p_right * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x += p_right * KEY_STP_SIZ;
			d->game->pos_y += p_left * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	check_step_3(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 180 && d->game->p_pos_dir < 270))
		return ;
	if (d->map->map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ + 0.1))] \
		[(int)(d->game->pos_x - p_left * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y + p_right * (KEY_STP_SIZ), \
			d->game->pos_x - p_left * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if (d->map->map[(int)(d->game->pos_y + p_right * (KEY_STP_SIZ))] \
			[(int)(d->game->pos_x - p_left * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x -= p_left * KEY_STP_SIZ;
			d->game->pos_y += p_right * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	check_step_4(t_data *d, float p_right, float p_left)
{
	if (!(d->game->p_pos_dir >= 270 && d->game->p_pos_dir < 360))
		return ;
	if (d->map->map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ + 0.1))] \
		[(int)(d->game->pos_x - p_right * (KEY_STP_SIZ + 0.1))] == '0')
	{
		if (corner_in_circle(d, d->game->pos_y - p_left * (KEY_STP_SIZ), \
			d->game->pos_x - p_right * (KEY_STP_SIZ)) == 1)
		{
			return ;
		}
		if (d->map->map[(int)(d->game->pos_y - p_left * (KEY_STP_SIZ))] \
			[(int)(d->game->pos_x - p_right * (KEY_STP_SIZ))] != '1')
		{
			d->game->pos_x -= p_right * KEY_STP_SIZ;
			d->game->pos_y -= p_left * KEY_STP_SIZ;
			d->ray->activate = 1;
		}
	}
}

void	player_step(t_data *d, int keycode)
{
	float	p_left;
	float	p_right;

	angle_calc(d->game->p_pos_dir % 90, keycode, &p_left, &p_right);
	check_step_1(d, p_right, p_left);
	check_step_2(d, p_right, p_left);
	check_step_3(d, p_right, p_left);
	check_step_4(d, p_right, p_left);
}
