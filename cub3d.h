
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
//# include LIBFT

typedef struct s_data
{
	void	*mlx;
	void	*win;

}	t_data;

// main.c
int		main(void);

// utils_free.c
void	free_data(t_data *d);

#endif