
#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define FILE_EMPTY 7
# define FILE_EMPT "File is empty or non-processable identifier found\n"
# define ARG_FAIL 8 // Too little arguments
# define ARG "Invalid number of arguments\n"
# define EXT_ERROR	9 // file-extension is wrong/missing
# define EXT "Usage: Extension invalid or missing...\n"
# define ALLOC_FAIL 10 // Allocation has failed 
# define ALLOC_F "Dynamic Allocation failed...\n"
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
# define RGB_MI 19
# define RGB_M "FILE invalid: unable to process RGB values..\n"
# define ORDER 20
# define ORDER_W "FILE invalid: map is not last\n"
# define MISSING_MAP 21
# define MISS_MAP "FILE invalid: file does not contain map or map not processable\n" 
# define ORDER_ID 22 
# define ORDER_I "FILE invalid: strict order of type identifiers violated\n"

# define BORDER "FILE invalid: map is not surrounded by walls...\n"
# define PLAYER "FILE invalid: none/too many players...\n"
# define CHARS "FILE invalid: invalid char found in map...\n"

struct	s_file; 
struct	s_data; 

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
int arguments_and_extension (int argc, char *str, int *error);
int		err_free_message(t_data *data, int error_code);

/*FUNCTIONS IN FILE utils_free.c*/
void	free_data(t_data *d);
void	free_array(char **arr); 

/*FUNCTIONS IN FILE init_data.c*/
void		init_data(t_data *d);

int process_map(t_data *data);
char **copy_map_parts_in_file(t_data *data, int begin);
int is_map_line(char *line);
int err_free_message(t_data *data, int error_code);

int is_c_space(char c);
int is_space(char *line);
int is_character(char c);
int is_wall_space(char c);
int file_length(char **arr);

void    init_map(t_data *data, char *argv);
int get_dimensions_of_file(t_data *d, char *argv);
int extract_textures(t_data *data, char **arr);
int *parse_rgb_colors(char *str, t_data *data);
int check_multiple_seperators(char *str);
int check_order_of_map(t_data *data);
int    create_file_array(t_data *d, char *argv); 
int is_valid_map_char(char c);
int order(char *trim, int *sum);
int check_order_of_file(t_data *data);
void textures_comp(char*trim, t_data *data, int *err, int *map);


#endif