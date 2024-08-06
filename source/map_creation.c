#include "../includes/cub3d.h"

static void process_file_to_stash(int *i, char *stash, char *line)
{
    size_t  j; 
    char    *nl_pos; 

    j = ft_strlen(line); 
    nl_pos = ft_strchr(line, '\n');
    if (nl_pos)
        j = nl_pos -line+1; 
    ft_memcpy(stash + *i, line, j);
    *i += j;
}

void    create_info_array(t_data *d, char *argv)
{
    char    *stash;
    char    *line;
    int     i;
    int     fd;

    i = 0;
    fd = open(argv, O_RDONLY);
    if(fd < 0)
        err_free_message(d, FD_ERROR); 
    line = get_next_line(fd);
    if(!line)
        err_free_message(d, ALLOC_FAIL); 
    stash = ft_calloc(sizeof(char), (d->x_file * d->y_file) + 1); 
    if(!stash)
    {
        free(line); 
        err_free_message(d, ALLOC_FAIL); 
    }
    while(line != NULL)
    {
        process_file_to_stash(&i, stash, line); 
        free(line); 
        line = get_next_line(fd);
    }
    stash[i] = '\0';
    close(fd);
    d->file_arr = ft_split(stash, '\n'); 
    free(stash);
    stash = NULL;
}

void get_dimensions_of_file(t_data *d, char *argv)
{
    int     fd; 
    char    *line; 
    int     max;
    int     count; 

    count = 0; 
    max = 0; 
    fd = open(argv, O_RDONLY); 
    if(fd < 0)
        err_free_message(d, FD_ERROR); 
    line = get_next_line(fd); 
    if(!line)
        err_free_message(d, MAP_EMPTY);   
    max = ft_strlen(line); 
    while(line != NULL)
    {
        count++; 
        free(line); 
        line = get_next_line(fd); 
        if((size_t)max < ft_strlen(line))
            max = ft_strlen(line); 
    }
    d->y_file = count;  
    d->x_file = max; 
    close(fd);
}

int check_multiple_seperators(char *str)
{
    int sep;
    int i;

    i = 0; 
    sep = 0; 
    while(str[i] && str[i + 1] != '\0')
    {
         if(str[i] == ',' && (str[i+1] == ',' || str[i+1]== '\0'))
            return(1); 
        i++; 
    } 
    return (0); 
}

int *parse_rgb_colors(char *str, t_data *data)
{
    char **rgb_values;
    int *rgb; 
    int i; 

    i= -1;
    if(check_multiple_seperators(str))
        err_free_message(data, FL_CEIL_M); 
    rgb = (int*)malloc(sizeof(int)*3); 
    rgb_values = ft_split(str, ',');
    if(!rgb_values)
    {
        return(free(rgb),NULL); 
    }
    while(++i < 3)
    {
        
        rgb[i] = ft_atoi(rgb_values[i]);
        if(rgb[i] < 0 || rgb[i] > 255)
            err_free_message(data, RGB_W); 
        free(rgb_values[i]); 
    }
    free(rgb_values); 
    return (rgb); 
}

static void textures_comp(char*trim, t_data *data)
{
    if(!ft_strncmp(trim, "NO ", 3))
    {
        if(data->file->elem->no_path != NULL)
            err_free_message(data, PERS_D); 
        data->file->elem->no_path = ft_strdup(trim + 3);
    }
    else if(!ft_strncmp(trim, "SO ", 3))
    {
        if(data->file->elem->so_path != NULL)
            err_free_message(data, PERS_D);
        data->file->elem->so_path = ft_strdup(trim + 3);
    }
    else if(!ft_strncmp(trim, "WE ", 3))
    {
        if(data->file->elem->we_path != NULL)
            err_free_message(data, PERS_D);
        data->file->elem->we_path = ft_strdup(trim + 3);
    }
    else if(!ft_strncmp(trim, "EA ", 3))
    {
        if(data->file->elem->ea_path != NULL)
            err_free_message(data, PERS_D);
        data->file->elem->ea_path = ft_strdup(trim + 3);
    }
    else if(!ft_strncmp(trim, "F ", 2))
    {
        if(data->file->elem->flo_rgb != NULL)
            err_free_message(data, FL_CEIL_D);
        data->file->elem->flo_rgb = parse_rgb_colors(trim + 2, data); 
    }
     else if(!ft_strncmp(trim, "C ", 2))
    {
        if(data->file->elem->ceil_rgb != NULL)
            err_free_message(data, FL_CEIL_D);
        data->file->elem->ceil_rgb = parse_rgb_colors(trim + 2, data);
        
    }
}

int extract_textures(t_data *data, char **arr)
{
    int i;
    char *trim; 

    i = -1;
    if(!arr)
        err_free_message(data, ALLOC_FAIL);
    while (arr[++i])
    { 
        trim = ft_strtrim(arr[i], " ");
        if(trim == NULL || trim[0] == '\0')
        {
            free(arr); 
            err_free_message(data, ALLOC_FAIL);     
        }
        textures_comp(trim, data);
        free(trim); 
    }
    return (0);
}

void    create_map_for_input_check(t_data *data, char *argv)
{
    get_dimensions_of_file(data, argv);
    create_info_array(data, argv);
    if(extract_textures(data, data->file_arr))
        err_free_message(data, IDENT_W);
    if(!data->file->elem->no_path || !data->file->elem->so_path || !data->file->elem->we_path || !data->file->elem->ea_path)
        err_free_message(data, PERS_M);
    if(!data->file->elem->flo_rgb || !data->file->elem->ceil_rgb)
        err_free_message(data, FL_CEIL_M);

    printf("Texture NO\n%s\n", data->file->elem->no_path);
    printf("Texture SO\n%s\n", data->file->elem->so_path);
    printf("Texture WE\n%s\n", data->file->elem->we_path);
    printf("Texture EA\n%s\n", data->file->elem->ea_path);
    printf("COLOR CEILING\n%d|%d|%d\n", data->file->elem->flo_rgb[0], data->file->elem->flo_rgb[1], data->file->elem->flo_rgb[2]);
    printf("COLOR FLOOR\n%d|%d|%d\n", data->file->elem->ceil_rgb[0], data->file->elem->ceil_rgb[1], data->file->elem->ceil_rgb[2]);
}
