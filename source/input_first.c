#include "../includes/cub3d.h"

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
        return(free(rgb),NULL); 
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

void textures_comp(char*trim, t_data *data, int *err, int *map)
{
    if(trim[1] == '\0')
        return ; 
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
    else if(!is_map_line(trim))
        (*map)++;
    else 
        (*err)++;  
}

int extract_textures(t_data *data, char **arr)
{
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int i;
    char *trim;
    int err;
    int map;

    i = 0;
    map = 0; 
    err = 0;
    if(!arr)
        return (1); 
    while (arr[i])
    { 
        trim = ft_strtrim(arr[i], " ");
        textures_comp(trim, data, &err, &map);
        free(trim);
        i++; 
    }
    printf("error __ %d\n", err); 
     printf("map __ %d\n", map);
    if(err)
    {
       err_free_message(data, FILE_EMPTY); 
    }
    if(!map)
        err_free_message(data, MISSING_MAP);
    return (0);
}

/*
    printf("Texture SO\n%s\n", data->file->elem->so_path);
    printf("Texture WE\n%s\n", data->file->elem->we_path);
    printf("Texture EA\n%s\n", data->file->elem->ea_path);
    printf("Texture NO\n%s\n", data->file->elem->no_path);
    printf("COLOR CEILING\n%d|%d|%d\n", data->file->elem->flo_rgb[0], data->file->elem->flo_rgb[1], data->file->elem->flo_rgb[2]);
    printf("COLOR FLOOR\n%d|%d|%d\n", data->file->elem->ceil_rgb[0], data->file->elem->ceil_rgb[1], data->file->elem->ceil_rgb[2])
*/