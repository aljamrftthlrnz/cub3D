
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
#include "libft/libft.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		error;
}	t_data;

// main.c
int		main(void);

// utils_free.c
void	free_data(t_data *d);

// init_data.c
void	init_data(t_data *d);


#endif