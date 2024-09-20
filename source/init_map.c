#include "../includes/cub3d.h"

int    create_file_array(t_data *d, char *argv)
{
    int fd;
    int i; 
    char *line;

    i = 0;
    fd = open(argv, O_RDONLY);
    if(fd < 0)
        return (1);
    line = get_next_line(fd);
    if(!line)
    {
        close (fd);
        return(1);
    }
    d->file_arr = (char **)ft_calloc((d->y_file + 1), sizeof(char*)); 
    if(!d->file_arr)
    {
        close (fd);
        free (line);
        return(1);
    }
    while(line && i < d->y_file)
    {
        d->file_arr[i] = (char*)ft_calloc(ft_strlen(line)+1, sizeof(char));
        if(!d->file_arr[i])
        {
            while(i > 0)
                free(d->file_arr[--i]);
            free(d->file_arr); 
            return(1); 
        }
        ft_strlcpy(d->file_arr[i], line, ft_strlen(line)+1);
        free(line);
        line = get_next_line(fd);
        i++; 
    }
    d->file_arr[i] = NULL;
    close(fd); 
    return (0); 
}

int get_dimensions_of_file(t_data *d, char *argv)
{
    int     fd; 
    char    *line; 
    int     max;
    int     count; 

    count = 0; 
    max = 0; 
    fd = open(argv, O_RDONLY); 
    if(fd < 0)
        return (1);
    line = get_next_line(fd);
    if(!line)
        return (1);
    max = ft_strlen(line);
    while(line != NULL)
    {
        count++; 
        free(line); 
        line = get_next_line(fd); 
        if((size_t)max < ft_strlen(line))
            max = ft_strlen(line); 
    }
    if (max < 3 || count < 1)
        return (1); 
    d->y_file = count;
    d->x_file = max;
    close(fd);
    return (0); 
}

void    init_map(t_data *data, char *argv)
{
    t_map *map; 

    map = data->map;
    if(get_dimensions_of_file(data, argv))
        err_free_message(data, FILE_EMPTY); 
    if(create_file_array(data, argv))
        err_free_message(data, FILE_EMPTY); 
    if(extract_textures(data, data->file_arr))
        err_free_message(data, IDENT_W);
    if(!data->elem->no_path || !data->elem->so_path || !data->elem->we_path || !data->elem->ea_path)
        err_free_message(data, PERS_M);
    if(!data->elem->flo_rgb || !data->elem->ceil_rgb)
        err_free_message(data, FL_CEIL_M);
    if(process_map(data))
       err_free_message(data, MISSING_MAP);
    if(check_order_of_file(data) != 6)
        err_free_message(data, ORDER_ID);
    if(check_order_of_map(data))
        err_free_message (data, ORDER);
    map_related_checks(data, map); 
 
}
