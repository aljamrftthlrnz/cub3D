
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define ARG_FAIL 8 // Too little arguments
# define ARG "Invalid number of arguments\n"
# define EXT_ERROR	9 // file-extension is wrong/missing
# define EXT "Usage: Extension invalid or missing...\n"
# define ALLOC_FAIL 10 // Allocation has failed 
# define ALLOC_F "Dynamic Allocation failed...\n"
# define FD_ERROR	11 // fd value is under 0
# define MAP_EMPTY	12 // **map-array is NULL
# define IDENT_W 13
# define IDENT "FILE invalid: type identifier has more than 2 characters...\n"
# define PERS_D 14
# define PERS "FILE invalid: perspective is double...\n"
# define PERS_M 15
# define PERS_MI "FILE invalid: perspective is missing...\n"
# define FL_CEIL_D 16
# define FLOOR_CEILING "FILE invalid: floor/ceiling is double...\n"
# define FL_CEIL_M 17
# define FL_CE_MISS "FILE invalid: unable to process floor/ceiling RGB values...\n" 
# define RGB_W 18
# define RGB_WRO "FILE invalid: RGB values are outside of range...\n"
# define RGB_W 18
# define IDENT_M "FILE invalid: type identifier is missing...\n"
# define RGB_M "FILE invalid: unable to process RGB values..\n"
# define BORDER "FILE invalid: map is not surrounded by walls...\n"
# define PLAYER "FILE invalid: none/too many players...\n"
# define CHARS "FILE invalid: invalid char found in map...\n"

struct	s_file; 
struct	s_data; 

// typedef enum element_status
// {
// 	NON, 
// 	VALID, // element has everything it needs; 
// 	// link with macro EXT_ERROR
// 	EXT_WRONG, // path has wrong extension
// 	EXT_MISS, // path has no extension 
// 	PERS_DOUBLE, // one/more perspective is double
// 	PERS_MISS, // perspective is missing 
// 	IDENT_WRONG, // type identifier has more than 2 characters
// 	FLOOR_CEIL_MISS, // floor or ceiling type missing 
// 	FLOOR_CEIL_DOUBLE, // floor or ceiling type double
// 	RGB_WRONG, // rgb isn't 0 - 255 	
// 	RGB_MISS // rgb under 3 elements
// } element_status; 

// typedef enum map_status
// {
// 	NOM, 
// 	VALID_MAP,// map is valid
// 	BORDER_WRONG, // map is not surrounded by 1 (walls)
// 	PLAY_WRONG, // map misses player/map has two players
// 	ORDER_WRONG, // map is not last in file
// } map_status; 

typedef struct s_element
{
	char			*we_path;
	char			*so_path;
	char			*no_path;
	char			*ea_path;
	int				*ceil_rgb;
	int				*flo_rgb;
	struct s_file	*file;
}	t_element;

typedef struct s_map
{
	char			**map;
	char			**cpy_map;
	int				length;
	int				width;
	int				p_pos_y;
	int				p_pos_x;
	struct s_file	*file;
} t_map;

typedef struct s_file 
{
	struct s_data	*data; // Use Forward declaration, is only init further down
	t_element		*elem;
	t_map			*map;
}	t_file; 

typedef struct s_data
{
	void	*mlx;
	void	*win; 
	int		error;
	char	**file_arr; 
	int		y_file; 
	int		x_file;
	t_file	*file; 
}	t_data;


/*FUNCTIONS IN FILE main.c*/
int		main(int argc, char**argv);
int		err_free_message(t_data *data, int error_code);

/*FUNCTIONS IN FILE utils_free.c*/
void	free_data(t_data *d);
void	free_array(char **arr); 

/*FUNCTIONS IN FILE init_data.c*/
void		init_data(t_data *d);

int			arguments_and_extension (int argc, char *str, int *error);
// void		get_length_of_file(t_data *d, char *argv); 
// void		get_longest_line(t_data *d, char *argv); 
void get_dimensions_of_file(t_data *d, char *argv); 
void		create_info_array(t_data *d, char *argv); 

void		init_node(t_element *new); 
t_element	*last_node(t_element *lst); 
void		add_node_to_linked_list(t_element **head, t_element *new); 
t_element	*init_new_node(char *arr, t_element *new);
int			intialize_base_zero(char **file_arr, t_element *e);
void create_prerequisites_for_input_checker(t_data *data);
void	print_list(t_element **head); 
void create_map_for_input_check(t_data *d, char *argv); 
int check_multiple_seperators(char *str); 

int err_free_message(t_data *data, int error_code); 
int extract_textures(t_data *data, char **arr);
int *parse_rgb_colors(char *str, t_data *data);



#endif