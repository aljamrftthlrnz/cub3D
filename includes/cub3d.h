
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
#include "libft/libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define EXT_ERROR	10
# define FD_ERROR	11
# define MAP_EMPTY	12

# define PERS "FILE invalid: perspective is double...\n"
# define PERS_M "FILE invalid: perspective is missing...\n"
# define IDENT "FILE invalid: type identifier has more than 2 characters...\n"
# define IDENT_M "FILE invalid: type identifier is missing...\n"
# define FLOOR_CEILING "FILE invalid: floor/ceiling is double...\n"
# define FL_CE_MISS "FILE invalid: floor/ceiling is missing...\n" 
# define RGB_WRO "FILE invalid: RGB values are outside of range...\n"
# define RGB_M "FILE invalid: RGB value missing...\n"

typedef enum type_status
{
	VALID, // element has everything it needs; 
	// link with macro EXT_ERROR
	EXT_WRONG, // path has wrong extension
	EXT_MISS, // path has no extension 
	PERS_DOUBLE, // one/more perspective is double
	PERS_MISS, // perspective is missing 
	IDENT_WRONG, // type identifier has more than 2 characters
	FLOOR_CEIL_MISS, // floor or ceiling type missing 
	FLOOR_CEIL_DOUBLE, // floor or ceiling type double
	RGB_WRONG, // rgb isn't 0 - 255 	
	RGB_MISS // rgb under 3 elements
} type_status; 

typedef enum map_status
{
	VALID_MAP,
	

}

typedef struct s_element
{
	char *string; 
	char *path; 
	char *type; 
	int *rgb; 
}	t_element; 

typedef struct s_file 
{
	t_data *d; 
	int y_axis; 
	int x_axis;
	t_element *e; 
}	t_file; 

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		error;
	char **file; 
	t_file *file; 
}	t_data;


/*FUNCTIONS IN FILE main.c*/
int		main(int argc, char**argv);

/*FUNCTIONS IN FILE utils_free.c*/
void	free_data(t_data *d);

/*FUNCTIONS IN FILE init_data.c*/
void	init_data(t_data *d);

int valid_extension (t_data *d, char *str); 
void get_length_of_file(t_data *d, char *argv); 
void get_longest_line(t_data *d, char *argv); 


#endif