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

void	pixel_to_img(t_image *img, int x, int y, int *rgb)
{
	int pixel_molecule = img->bits_per_pixel / 8;
	// int i = pixel_molecule;
	int position;

	position = y * img->size_line * pixel_molecule;
	printf("position: %d\n", position);
	position = position + (x * pixel_molecule);
	printf("position: %d\n", position);


	(void) rgb;

}


void	setup_img(t_data *d, t_image *new_img)
{
	new_img->img_ptr = mlx_new_image(d->mlx, 1, 1);
	new_img->img_adr = mlx_get_data_addr(new_img->img_ptr, &new_img->bits_per_pixel, &new_img->size_line, &new_img->endian);
}

void	creates_img(t_data *d)
{
	int rgb[3];

	rgb[1] = 128;
	rgb[2] = 0;
	rgb[3] = 128;

	setup_img(d, d->img);

	pixel_to_img(d->img, 0, 1, rgb);


	// d->img->img_adr[1] = 128;
	// d->img->img_adr[2] = 0;
	// d->img->img_adr[3] = 128;


	// printf("bits_per_pixel: %d\nsize_line: %d\nendian: %d\n", bits_per_pixel, size_line, endian);
	// printf("---img address\n\n");
	// while (i < size_line)
	// {
	// 	printf("%d\n", d->img->img_adr[i]);
	// 	// write(1, &d->img->img_adr[i], 1);
	// 	i++;
	// }


	// mlx_put_image_to_window(d->mlx, d->win, d->img->img_ptr, 5, 5);
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
	d->img = (t_image *) malloc(sizeof(t_image));
	if (d->img == NULL)
	{
		free_data(d);
		return (1);
	}
	creates_img(d);
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