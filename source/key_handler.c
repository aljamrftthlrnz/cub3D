/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:20 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:54:21 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// closes game on X button or ESC key
int	close_game(void *ptr)
{
	t_data	*d;

	d = (t_data *)ptr;
	write(2, "game turned off\n", 17);
	mlx_loop_end(d->mlx);
	free_mlx(d);
	free_data(d);
	exit(0);
}

int	key_handler(int keycode, void *d_ptr)
{
	t_data	*d;

	d = d_ptr;
	if (keycode == ESC)
	{
		close_game(d);
	}
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A \
		|| keycode == KEY_D)
	{
		player_step(d, keycode);
		return (0);
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		arrow_keys(d, keycode);
		d->ray->activate = 1;
		return (0);
	}
	return (0);
}

void	setup_key_buttons(t_data *d)
{
	mlx_hook(d->win, 17, 1L << 2, &close_game, d);
	mlx_hook(d->win, 2, 1L << 0, &key_handler, d);
}
