/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:55:01 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:55:02 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	determine_distance_to_wall(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_distx - ray->delta_distx);
	else
		ray->perp_wall_dist = (ray->side_disty - ray->delta_disty);
}

void	wall_hit(t_map *map, t_raycast *ray)
{
	int	loop;

	loop = 0;
	while (!ray->hit && loop < 400)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapx < 0 || ray->mapx >= map->width || ray->mapy < 0 \
			|| ray->mapy >= map->length)
			return ;
		if (map->map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
		loop++;
	}
}

void	position_and_stepvalues(t_game *g, t_raycast *r)
{
	if (r->ray_dirx < 0)
	{
		r->stepx = -1;
		r->side_distx = (g->pos_x - r->mapx) * r->delta_distx;
	}
	else
	{
		r->stepx = 1;
		r->side_distx = (r->mapx + 1.0 - g->pos_x) * r->delta_distx;
	}
	if (r->ray_diry < 0)
	{
		r->stepy = -1;
		r->side_disty = (g->pos_y - r->mapy) * r->delta_disty;
	}
	else
	{
		r->stepy = 1;
		r->side_disty = (r->mapy + 1.0 - g->pos_y) * r->delta_disty;
	}
}

void	init_loop(int x, t_raycast *r, t_game *g)
{
	r->camera_x = 2 * x / (double) SCREEN_W - 1;
	r->ray_dirx = g->dir_x + r->plane_x * r->camera_x;
	r->ray_diry = g->dir_y + r->plane_y * r->camera_x;
	r->mapx = (int)g->pos_x;
	r->mapy = (int)g->pos_y;
	if (r->ray_dirx == 0)
		r->delta_distx = 1e30;
	else
		r->delta_distx = fabs(1 / r->ray_dirx);
	if (r->ray_diry == 0)
		r->delta_disty = 1e30;
	else
		r->delta_disty = fabs(1 / r->ray_diry);
}

void	ray_loop(t_data *d)
{
	int	x;

	x = 0;
	while (x < SCREEN_W)
	{
		init_loop(x, d->ray, d->game);
		position_and_stepvalues(d->game, d->ray);
		wall_hit(d->map, d->ray);
		if (d->ray->hit == 1)
		{
			determine_distance_to_wall(d->ray);
			vertical_line_height(d->elem, d->ray, d->game);
			decide_map_texture(d->ray, d->elem);
		}
		render_column(d, x);
		d->ray->hit = 0;
		x += LINE_W;
	}
}
