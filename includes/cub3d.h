
# ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# include <stdint.h>
# include <math.h>

# include <sys/time.h>

# include "libft/libft.h"

# define SCREEN_W 800
# define SCREEN_H 800

# define LINE_W 1
// # define SCREEN_W 100
// # define SCREEN_H 80

# define PLANE 0.66

# define texSize		64

# define FPS		60	
# define PI			3.141592653589793
# define DEGREES	90

# define FRMRT 16

# define DIR_N 0
# define DIR_E 90
# define DIR_S 180
# define DIR_W 270

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

# define MAX_LENGTH 
# define MAX_WIDTH 

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define KEY_STP_SIZ 0.1
# define KEY_ROT_ANGL 4


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
# define MLXIMG 102
# define MLXIMG_M "mlx image creation failed\n"
# define MLXSIZ 103
# define MLXSIZ_M "given textures are not of size 64x64\n"

# define ISLE 150
# define ISLE_M "MAP invalid: islands detected...\n"



struct	s_file; 
struct	s_data; 

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


typedef struct s_raycast
{
	double		rot_speed;
	double		moveSpeed; 
	double		plane_x;
	double		plane_y;		
	double		camera_x;
	double		camera_y;		
	double		rayDirX;
	double		rayDirY;		
	double		deltaDistX;
	double		deltaDistY;
    double		sideDistX;
    double		sideDistY;		
	double		perpWallDist;
	double 		time; 
	double		oldtime;
	int			stepX;
    int			stepY;		
	int			mapX;
    int			mapY;
	int			side;
	int			hit;
	double 		frameTime;
	
	int			wall_collide; 
	int			activate;

} t_raycast;

typedef struct s_element
{
	char			*we_path;
	char			*so_path;
	char			*no_path;
	char			*ea_path;
	int				*ceil_rgb;
	int				*flo_rgb;
	int				texnum; 
	int 			texx;
	int				texy;
	int				width; 
	int 			height; 
	double			wallx;
	double			step;
	double			texpos;
	int				line_height;
    int				drawStart;
    int				drawEnd;
	uint32_t		color;
	int				**texture;
	int				**texel;
}	t_element;

typedef struct s_game
{
	double			pos_y;
	double			pos_x;
	double			dir_x; 
	double			dir_y;
	int				p_pos_dir; 
}	t_game;


typedef struct s_map
{
	char			**map;
	char			**cpy_map;
	char			**flood_map;
	int				length;
	int				width;
	int				pos_y;
	int				pos_x;
	int				p_pos_dir;
} t_map;
typedef struct s_data
{
	void		*mlx;
	void		*win; 
	int			error;
	char		**file_arr; 
	int			y_file; 
	int			x_file;
	t_element	*elem;
	t_map		*map;
	t_raycast	*ray;
	t_game		*game;
	t_image		*NESW;
	t_image 	*screen;
}	t_data;
// typedef struct s_file 
// {
// 	struct s_data	*d; // Use Forward declaration, is only init further down
// 	t_element		*elem;
// 	t_map			*map;
// }	t_file; 

/* anti_island_checker.c */
void	flood_alloc(t_data *d, t_map *map);
int	print_matrix(char **matrix, int nl); // not needed in final version
int	char_condition(char c, char f);
int	floodfill(t_map *map, int x, int y);
void	anti_island_checker(t_data *d, t_map *map);


/* check_map.c */
char 	**create_map_copy(t_map *map);
void    get_player_direction_position(int y, int x, t_map *m);
int		replace_spaces_and_check_player(t_map *map, char **s);
int		check_empty_lines_in_map(t_map *m);
void	map_related_checks(t_data *d, t_map *map);

/* check_map_2.c */
int		validating_map_content(char **s);
int		check_up_down_left_right(char **map, int i, int j);
int		loop_over_potential_walls(char *s);
int		validate_outer_walls(char *cpy);
int		validating_map_walls(char **cpy);

/* create_game.c */
int		time_to_render(t_data *d);
int		render_frame(t_data *d);
void	create_game(t_data *d);

/* create_map.c */
int		is_valid_map_char(char c);
int		is_map_line(char *line);
int		calc_map_size(t_data *d, int begin);
char	**copy_map_parts_in_file(t_data *d, int begin);
int		process_map(t_data *d);

/*FUNCTIONS IN FILE error.c*/
void	free_element(t_element *e);
void	free_data(t_data *d);
void	free_mlx(t_data *d);
void	free_array(char **arr);
void	print_error_2(int error_code);
void	print_error(int error_code);
int 	err_free_message(t_data *d, int error_code);

/* img_utils.c */
int		img_get_pos(t_image *img, int x, int y);
void	pixel_to_img(t_image *img, int x, int y, int *rgb);
void	fill_color_img(t_image *image, int *rgb);
void	copy_pos_to_img(t_image *d_img, t_image *s_img, int d_pos, int s_pos);

/*FUNCTIONS IN FILE init_data.c*/
void 	init_element(t_element *e);
void 	init_raycast(t_raycast *ray);
void	 init_data_struct(t_data *d);
void	 rotation(t_raycast *r);
void	 init_data(t_data *d);

/* init_img.c */
void	setup_img(t_data *d, t_image *new_img, char *path);
void	init_img(t_data *d);

/* init_map_helper.c */
int is_space(char *line);
int is_character(char c);
int is_wall_space(char c);
int file_length(char **arr);
int map_len(char **arr);

/* init_map.c */
int		setup_file(t_data *d, int *fd, char **line, char *argv);
int    create_file_array(t_data *d, char *argv);
int		get_dimensions_of_file(t_data *d, char *argv);
void	replace_initial_player_pos(t_map *m);
int		get_map_length(char **map);
void    init_map(t_data *d, char *argv);

/* input_first.c */
int *parse_rgb_colors(char *str, t_data *d, char *ptr);
char	*parse_texture(t_data *d, char *trim);
int	is_identifier(t_data *d, void **path, char *id, char *trim);
void textures_comp(char*trim, t_data *d, int *map);
int extract_textures(t_data *d, char **arr);

/* input_second.c */
int check_multiple_seperators(char *str);
int check_order_of_map(t_data *d);

/* key_handler.c */
int		close_game(void *ptr);
int		key_handler(int keycode, void *d);
void	setup_key_buttons(t_data *d_ptr);

/*FUNCTIONS IN FILE main.c*/
void	init_game(t_data *d);
void	play_game(t_data *d);
int			arguments_and_extension (int argc, char *str, int *error);
int			main(int argc, char**argv);

/* open_window.c */
void	open_window(t_data *d);

// player_movement.c
void	arrow_keys(t_data *d, int keycode);
void    normalize_vector(double *x, double *y);
void	angle_calc(int angle, int keycode, double *p_left, double *p_right);
void	player_step(t_data *d, int keycode);

/* raycast_loop.c */
void vertical_line_height(t_element *e, t_raycast *ray, t_game *g);
void determine_distance_to_wall(t_raycast *ray, t_game *game);
void wall_hit(t_map *map, t_raycast *ray);
void position_and_stepvalues(t_game *g, t_raycast *r);
void init_loop(int x, t_raycast *r, t_game *g);
void ray_loop(t_data *d);

/* raycast_texture.c */
void decide_map_texture(t_raycast *r, t_element *e);
void handle_texture_update(t_raycast *r, t_element *e);

/* raycast.c */
void init_north_south(t_game *g, t_raycast *r);
void init_east_west(t_game *g, t_raycast *r);
void init_raycasting(t_raycast *r, t_map *map, t_game *g);
double   avoid_zero_at_all_costs(double definitely_not_zero);

/* render_column.c */
void	img_dis_col(t_data *d, double h, double x, double y);
void	render_column(t_data *d, int x);

/* render_c_f.c */
void	color_below(t_data *d, double ray_hit_wall_x, double ray_hit_wall_y);
void	color_above(t_data *d, int wall_height, double ray_hit_wall_x, double ray_hit_wall_y);

#endif