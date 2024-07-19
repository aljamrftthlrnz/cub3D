#include <mlx.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>


#define ESC 65307

int	mini_close_game(int keycode, void *mlx)
{
	(void)keycode;
	write(2, "game turned off\n", 17);

	mlx_loop_end(mlx);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
	exit(0);
}
int	mini_key_handle(int keycode, void *mlx)
{
	if (keycode == ESC)
		mini_close_game(1, mlx);
	return 0;
}

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (mlx == NULL)
		return (1);
	win = mlx_new_window(mlx, 5 * 32, 5 * 32, "window_name");
	if (win == NULL)
		return (1);
	mlx_key_hook(win, mini_key_handle, mlx);
	// mlx_loop_hook(mlx, NULL, NULL);
	mlx_loop(mlx);
	return (0);

}