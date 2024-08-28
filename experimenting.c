#include "cub3d.h"

// this one was used for the ESC
int	mini_close_game(int keycode, void *ptr)
{
	t_data *d;

	d = (t_data *)ptr;
	(void)keycode;
	write(2, "game turned off\n", 17);

	mlx_loop_end(d->mlx);
	free_data(d);
	exit(0);
}

// this one is used for the X button, since the function is a parameter and can't take a keycode
int	mini_close_game_2(void *ptr)
{
	t_data *d;

	d = (t_data *)ptr;
	write(2, "game turned off\n", 17);

	mlx_loop_end(d->mlx);
	free_data(d);
	exit(0);
}


void	step_forward(t_data *d)
{
	int	angle = d->map->player_sight % 90;
	float	p_left;
	float	p_right;

	printf("angle: %d\n", angle);
	p_left = (float) angle / 9 / 10;
	p_right = 1 - p_left;
	printf("px: %f\npy: %f\n", p_left, p_right);

	if (d->map->player_sight < 90)
	{
		d->map->player_x += p_left;
		d->map->player_y -= p_right;
	}
	else if (d->map->player_sight < 180)
	{
		d->map->player_x += p_right;
		d->map->player_y += p_left;
	}
	else if (d->map->player_sight < 270)
	{
		d->map->player_x -= p_left;
		d->map->player_y += p_right;
	}
	else if (d->map->player_sight < 360)
	{
		d->map->player_x -= p_right;
		d->map->player_y -= p_left;
	}
}

int wasd_keys(void *ptr, int key)
{
	t_data *d;
	// float	step_x;
	// float	step_y;

	d = (t_data *)ptr;
	if (key == W ) //&& d->map->matrix[(d->map->player_y - 1) / 32][d->map->player_x / 32] != '1')
	{
		step_forward(d);
		// d->map->player_y -= 1;
	}
	if (key == A && d->map->matrix[(int) d->map->player_y / 32][((int) d->map->player_x - 1) / 32] != '1')
	{
		d->map->player_x -= 1;
	}
	if (key == S && d->map->matrix[((int) d->map->player_y + 1) / 32][(int) d->map->player_x / 32] != '1')
	{
		d->map->player_y += 1;
	}
	if (key == D && d->map->matrix[((int) d->map->player_y - 1) / 32][((int) d->map->player_x + 1) / 32] != '1')
	{
		d->map->player_x += 1;
	}
	return (0);
}

void	arrow_keys(t_data *d, int keycode)
{
	if (keycode == LEFT)
	{
		d->map->player_sight -= 2;
	}
	if (keycode == RIGHT)
	{
		d->map->player_sight += 2;
	}
	while (d->map->player_sight < 0)
		d->map->player_sight = 360 + d->map->player_sight;
	while (d->map->player_sight > 359)
		d->map->player_sight = d->map->player_sight - 360;
	printf("direction: %d\n", d->map->player_sight);
}

int	mini_key_handle(int keycode, void *d)
{
	if (keycode == ESC)
		mini_close_game_2(d);
	if (keycode == W)
		wasd_keys(d, W);
	if (keycode == A)
		wasd_keys(d, A);
	if (keycode == S)
		wasd_keys(d, S);
	if (keycode == D)
		wasd_keys(d, D);
	if (keycode == LEFT || keycode == RIGHT)
		arrow_keys(d, keycode);


	return 0;
}

// int	mini_keypress_handle(void *d)
// {

// 	return (0);
// }

void	setup_key_hooks(t_data *d)
{
	// keys (just press):
	// mlx_key_hook(d->win, mini_key_handle, d); //not needed since every key is handled in mlx_hook
	// keys (including hold):
	mlx_hook(d->win, 2, 1L << 0, &mini_key_handle, d);
	// X button:
	mlx_hook(d->win, 17, 1L << 2, &mini_close_game_2, d);

}

void	setup_loop_hooks(t_data *d)
{
	mlx_loop_hook(d->mlx, render_frame, d);
}

int	main(void)
{
	t_data *d;

	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		return (1);
	d->mlx = mlx_init();
	if (d->mlx == NULL)
	{
		free_data(d);
		return (1);
	}
	if (init_mock_map(d) != 0)
	{
		free_data(d);
		return (1);
	}
	d->win = mlx_new_window(d->mlx, d->map->map_width * 32, d->map->map_height * 32, "window_name");
	if (d->win == NULL)
	{
		free_data(d);
		return (1);
	}
	setup_key_hooks(d);
	setup_loop_hooks(d);
	while (1)
	{
		usleep(100000);
		mlx_loop(d->mlx);
	}
	free_data(d);
	return (0);

}