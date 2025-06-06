/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:53:13 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:53:14 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_element(t_element *e)
{
	e->texnum = -1;
	e->width = TEXSIZE;
	e->height = TEXSIZE;
}

void	init_raycast(t_raycast *ray)
{
	ray->move_speed = 0.0;
	ray->rot_speed = 0.0;
	ray->frame_time = 0.0;
	ray->activate = 1;
}

void	init_data_struct(t_data *d)
{
	d->mlx = NULL;
	d->win = NULL;
	d->error = 0;
	d->file_arr = NULL;
	d->x_file = 0;
	d->y_file = 0;
	d->elem = NULL;
	d->map = NULL;
	d->ray = NULL;
	d->game = NULL;
	d->nesw = NULL;
	d->screen = NULL;
}

void	init_data(t_data *d)
{
	init_data_struct(d);
	d->elem = (t_element *) ft_calloc(sizeof(t_element), 1);
	if (!d->elem)
		err_free_message(d, ALLOC_FAIL);
	init_element(d->elem);
	d->map = (t_map *) ft_calloc(sizeof(t_map), 1);
	if (!d->map)
		err_free_message(d, ALLOC_FAIL);
	d->ray = (t_raycast *) ft_calloc(sizeof(t_raycast), 1);
	if (!d->ray)
		err_free_message(d, ALLOC_FAIL);
	init_raycast(d->ray);
	d->game = (t_game *) ft_calloc(sizeof(t_game), 1);
	if (!d->game)
		err_free_message(d, ALLOC_FAIL);
	return ;
}
