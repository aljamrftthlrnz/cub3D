/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:52:48 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:52:49 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	time_to_render(t_data *d)
{
	struct timeval	t;
	static long		time = 0;
	long			time_new_ms;
	t_raycast		*r;

	r = d->ray;
	gettimeofday(&t, NULL);
	time_new_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if (time + (1000 / FRMRT) <= time_new_ms)
	{
		time = time_new_ms;
		return (1);
	}
	return (0);
}

int	render_frame(t_data *d)
{
	if (time_to_render(d) == 1 && d->ray->activate == 1)
	{
		ray_loop(d);
		mlx_put_image_to_window(d->mlx, d->win, d->screen->img_ptr, 0, 0);
		d->ray->activate = 0;
	}
	return (0);
}

void	create_game(t_data *d)
{
	setup_key_buttons(d);
	mlx_loop_hook(d->mlx, &render_frame, d);
	mlx_loop(d->mlx);
}
