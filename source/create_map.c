#include "../includes/cub3d.h"

int is_map_line(char *line)
{
    int i; 

    i = 0; 
    while(line[i])
    {
        if(!is_wall_space(line[i]) && !is_character(line[i]) && !is_c_space(line[i]))
            return (1); 
        i++; 
    }
    return(0);
}

char **copy_map_parts_in_file(t_data *data, int begin)
{
    char **map;
    int j;
    int map_size;

    j = 0;
    map_size = file_length(data->file_arr) - begin;
    
    map = (char**)ft_calloc(map_size + 1, sizeof(char*)); 
    if (!map)
        return (NULL);
    while (j < map_size)
    {
        map[j] = (char*)ft_calloc(ft_strlen(data->file_arr[begin]) + 1, sizeof(char)); 
        if (!map[j])
        {
            while (j > 0)
                free(map[--j]);
            free(map);
            return (NULL); 
        }
        ft_strlcpy(map[j], data->file_arr[begin], ft_strlen(data->file_arr[begin]) + 1); 
        j++;
        begin++;
    }
    map[j] = NULL; // Null-terminate the array of strings
    return(map); 
}

int process_map(t_data *data)
{
    int i;
    int begin; 
    char **arr; 

    i = 0;
    begin = 0;
    arr = data->file_arr;
    while(arr[i] != NULL && is_map_line(arr[i]))
        i++; 
    if (arr[i] == NULL)
        return(1); 
    else
        begin = i;
    data->file->map->map = copy_map_parts_in_file(data, begin);
    // for (int i = 0; data->file->map->map[i]; i++)
    //     printf("Line ___ %s\n", data->file->map->map[i]); 
    if(data->file->map->map == NULL)
        return (1); 
    return (0); 
}
