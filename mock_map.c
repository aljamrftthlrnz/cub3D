#include "cub3d.h"



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
	d->map->img_WE = mlx_xpm_file_to_image(d->mlx, "./pics/frog_down.xpm", &img_size, &img_size);
	d->map->img_SO = mlx_xpm_file_to_image(d->mlx, "./pics/wall_1.xpm", &img_size, &img_size);
	d->map->matrix = fill_mock_map();
	// d->map->map = calloc();
	d->map->map_height = 5;
	d->map->map_width = 6;
	// d->map->player_x = 5;
	// d->map->player_y = 4;
	d->map->player_x = 4 * 32 + 16;
	d->map->player_y = 3 * 32 + 16;
	d->map->player_dir = NORTH;
	d->map->player_dir = 0;
	// no null check because fuck testing
	return (0);
}