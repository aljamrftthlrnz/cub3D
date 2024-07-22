#include "cub3d.h"

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
int	mini_key_handle(int keycode, void *mlx)
{
	if (keycode == ESC)
		mini_close_game(1, mlx);
	return 0;
}

void	free_data(t_data *d)
{
	if (d->win)
	{
		mlx_destroy_window(d->mlx, d->win);
	}
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	free(d);
}

void init_map(t_map *map)
{
	map->ceiling_color = NULL;
	map->floor_color = NULL;
	map->img_EA = NULL;
	map->img_NO = NULL;
	map->img_WE = NULL;
	map->img_SO = NULL;
	map->matrix = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
}


char **fill_mock_map(void) { //testing purposes
	// Step 1: Determine the size of the matrix
	int rows = 5;
	int cols = 6;

	// Step 2: Allocate memory for rows
	char **matrix = malloc(rows * sizeof(char*));
	if (!matrix) {
		printf("Memory allocation failed\n");
		return (NULL);
	}

	// Step 3: Allocate memory for each row
	for (int i = 0; i < rows; i++) {
		matrix[i] = malloc((cols + 1) * sizeof(char)); // +1 for null terminator
		if (!matrix[i]) {
			printf("Memory allocation failed\n");
			return (NULL);
		}
	}

	// Step 4: Fill the matrix with values
	const char* patterns[5] = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111"
	};

	for (int i = 0; i < rows; i++) {
		strcpy(matrix[i], patterns[i]);
	}

	return (matrix);
}


int	init_mock_map(t_data *d) //testing purposes
{
	int	img_size;

	d->map = (t_map *) malloc(sizeof(t_map));
	if (d->map == NULL)
		return (1);
	init_map(d->map);
	d->map->ceiling_color = calloc(sizeof(int), 3);
	d->map->floor_color = calloc(sizeof(int), 3);
	d->map->img_EA = mlx_xpm_file_to_image(d->mlx, "./pics/exit_1.xpm", &img_size, &img_size);
	d->map->img_NO = mlx_xpm_file_to_image(d->mlx, "./pics/flower_0.xpm", &img_size, &img_size);
	d->map->img_WE = mlx_xpm_file_to_image(d->mlx, "./pics/drog_down.xpm", &img_size, &img_size);
	d->map->img_SO = mlx_xpm_file_to_image(d->mlx, "./pics/wall_1.xpm", &img_size, &img_size);
	d->map->matrix = fill_mock_map();
	// d->map->map = calloc();
	d->map->map_height = 5;
	d->map->map_width = 6;
	d->map->player_x = 5;
	d->map->player_y = 4;
	d->map->player_dir = NORTH;
	// no null check because fuck testing
	return (0);
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
	mlx_key_hook(d->win, mini_key_handle, d);
	// mlx_loop_hook(mlx, NULL, NULL);
	mlx_loop(d->mlx);
	free_data(d);
	return (0);

}