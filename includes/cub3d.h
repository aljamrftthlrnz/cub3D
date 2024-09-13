
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

# define MAX_LENGTH 
# define MAX_WIDTH 

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define DIR_N 0
# define DIR_E 90
# define DIR_S 180
# define DIR_W 270


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
# define EMPTY_LINES 23
# define EMPTY_L "MAP invalid: empty lines in map found\n"
# define BORDER_M 24
# define BORDER "MAP invalid: map is not surrounded by walls...\n"
# define PLAYER_W 25
# define PLAYER "MAP invalid: none/too many players...\n"
# define PLAYER_MO 26
# define PLAYER_M "MAP invalid: player is not able to move around the map\n"
# define SPACE_PROT 27
# define SPACE "MAP invalid: spaces are not secured properly\n"

# define MLXIN 100
# define MLXIN_M "mlx initialization failed\n"
# define MLXWI 101
# define MLXWI_M "mlx window creation failed\n"


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
	int				p_pos_dir;
	struct s_file	*file;
} t_map;

typedef struct s_file 
{
	struct s_data	*data; // Use Forward declaration, is only init further down
	t_element		*elem;
	t_map			*map;
}	t_file; 


typedef struct s_image
{
	void	*img_ptr;
	char	*img_adr;
	
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	int		height;
	int		width;

}	t_image;

typedef struct s_game 
{
	float	player_x;
	float	player_y;
	int		player_dir;
}	t_game;


typedef struct s_data
{
	void	*mlx;
	void	*win; 
	int		error;
	char	**file_arr; 
	int		y_file; 
	int		x_file;
	t_file	*file; 
	t_game	*game;
}	t_data;




/*FUNCTIONS IN FILE main.c*/
void	init_game(t_data *d);
int		main(int argc, char**argv);
int arguments_and_extension (int argc, char *str, int *error);
int		err_free_message(t_data *data, int error_code);
void	play_game(t_data *d);


/*FUNCTIONS IN FILE error.c*/
void	free_mlx(t_data *d);
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
int *parse_rgb_colors(char *str, t_data *data, char *ptr);
int check_multiple_seperators(char *str);
int check_order_of_map(t_data *data);
int    create_file_array(t_data *d, char *argv); 
int is_valid_map_char(char c);
int order(char *trim, int *sum);
int check_order_of_file(t_data *data);
void textures_comp(char*trim, t_data *data, int *err, int *map);
int replace_spaces_and_check_player(t_map *map, char **s); 
int check_empty_lines_in_map(t_map *m); 
char **create_map_copy(t_map *map); 
int validating_map_walls(char **cpy); 
int loop_over_potential_walls(char *s);
int validate_outer_walls(char *cpy);
void map_related_checks(t_map *map);
int check_up_down_left_right(char **map, int i, int j);
int validating_map_content(char **s);
int map_len(char **arr);


// check_map.c
void    get_p_dir(t_map *map, char dir);




// open_window.c
void	open_window(t_data *d);

// create_game.c
int		render_frame(t_data *d);
void	create_game(t_data *d);

// key_handler.c
int		close_game(void *ptr);
int		key_handler(int keycode, void *d);
void	setup_key_buttons(t_data *d);

// player_movement.c
void	arrow_keys(t_data *d, int keycode);
void	angle_calc(int angle, int keycode, float *p_left, float *p_right);
void	player_step(t_data *d, int keycode);


#endif