#include "../includes/cub3d.h"

int *parse_rgb_colors(char *str, t_data *data, char *ptr)
{
    char **rgb_values;
    int *rgb; 
    int i;
    int num; 

    i= -1;
    if(check_multiple_seperators(str))
    {
        free(ptr);
        err_free_message(data, FL_CEIL_M);
    }
    rgb_values = ft_split(str, ',');
    if(!rgb_values)
    {
        free (ptr);
        err_free_message(data, ALLOC_FAIL);
    }
    num = file_length(rgb_values);
    if(num > 3)
    {
        free_array(rgb_values);
        free(ptr);
        err_free_message(data, FL_CEIL_M);
    }
    rgb = (int*)malloc(sizeof(int)*3); 
    if (rgb == NULL)
    {
        free_array(rgb_values);
        free(ptr);
        err_free_message(data, ALLOC_FAIL);
    }
    while(++i < 3)
    {
        rgb[i] = ft_atoi(rgb_values[i]);
        if(rgb[i] < 0 || rgb[i] > 255)
        {
            free(rgb);
            free_array(rgb_values);
            free(ptr);
            err_free_message(data, RGB_W); 
        }
    }
    free_array(rgb_values);
    return (rgb); 
}

void textures_comp(char*trim, t_data *data, int *err, int *map)
{
    if(!is_map_line(trim))
    {
        //printf("map line[%s]", trim); 
        (*map)++;
    }
    else if(!ft_strncmp(trim, "NO ", 3))
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
        data->file->elem->flo_rgb = parse_rgb_colors(trim + 2, data, trim); 
    }
    else if(!ft_strncmp(trim, "C ", 2))
    {
        if(data->file->elem->ceil_rgb != NULL)
            err_free_message(data, FL_CEIL_D);
        data->file->elem->ceil_rgb = parse_rgb_colors(trim + 2, data, trim);
    }
    else 
    {
        (*err)++;  
        //printf("error found with [%s]\n", trim);
    }
}

int extract_textures(t_data *data, char **arr)
{
   int i;
   int err;
   int map;
   char *trim;

   i = 0;
   err = 0;
   map = 0;
   trim = NULL;
   if(!arr)
        return (1);
    while(arr[i])
    {
        if(!arr[i])
            break ;
        if(arr[i] && !is_space(arr[i]))
        {
            //printf("is space\n");
            i++; 
            continue ;   
        }
        else 
        {
            //printf("is not space \n");
            trim = ft_strtrim(arr[i], " ");
            if(trim == NULL || trim[0] == '\0')
            {
                //printf("NOW-----------\n");    
                return (free(trim), 1);
            }
            //printf("Trimmed -%s-\n", trim); 
            textures_comp(trim, data, &err, &map);
            free (trim);  
            trim = NULL;
            i++;
        }        
    }
    if(err)
       err_free_message(data, FILE_EMPTY); 
    if(!map)
        err_free_message(data, MISSING_MAP);
    return (0);
}

/*
    //printf("map lines ___ %d\n", map);
    //printf("error counter ___ %d\n", err); 

    printf("Texture SO\n%s\n", data->file->elem->so_path);
    printf("Texture WE\n%s\n", data->file->elem->we_path);
    printf("Texture EA\n%s\n", data->file->elem->ea_path);
    printf("Texture NO\n%s\n", data->file->elem->no_path);
    printf("COLOR CEILING\n%d|%d|%d\n", data->file->elem->flo_rgb[0], data->file->elem->flo_rgb[1], data->file->elem->flo_rgb[2]);
    printf("COLOR FLOOR\n%d|%d|%d\n", data->file->elem->ceil_rgb[0], data->file->elem->ceil_rgb[1], data->file->elem->ceil_rgb[2])
*/
