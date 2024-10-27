/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:49 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:54:50 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// initializes mlx and window; sets up key handling; starts the loop
void	open_window(t_data *d)
{
	d->win = mlx_new_window(d->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (d->win == NULL)
	{
		free_mlx(d);
		err_free_message(d, MLXWI);
		return ;
	}
}
