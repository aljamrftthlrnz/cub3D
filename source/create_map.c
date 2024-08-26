#include "../includes/cub3d.h"

int is_valid_map_char(char c)
{
    if(c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '\n')
        return (1); 
    return (0); 
}

int is_map_line(char *line)
{
    int i; 

    i = 0;
    if(!is_space(line))
        return (1);  
    while(line[i] && line[i] != '\n')
    {
        if(!is_valid_map_char(line[i]))
        {
            //printf("Char is [%d]...\n", line[i]);
            return (1); 
        }
        i++; 
    }
    //printf("MAP\n"); 
    return(0);
}

int calc_map_size(t_data *data, int begin)
{
    int size;
    int i;

    i = file_length(data->file_arr) - 1;
    while(data->file_arr[i] && !is_space(data->file_arr[i]))
        i--;
    size = i - begin; 
    return (size);
}

char **copy_map_parts_in_file(t_data *data, int begin)
{
    char **map;
    int j;
    int map_size;

    j = 0;
    map_size = calc_map_size(data, begin) + 1;
    //printf("The map size ___ %d\n", map_size); 
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
    int res; 
    char **arr; 

    i = 0;
    begin = 0;
    arr = data->file_arr;
    while(arr[i] != NULL)
    {
        res = is_map_line(arr[i]);
        if(res == 0)
            break; 
        i++; 
    }
    if (arr[i] == NULL)
        return(1); 
    begin = i;
    //printf("Begin ____ %d\n",   i); 
    data->file->map->map = copy_map_parts_in_file(data, begin);
    // for (int i = 0; data->file->map->map[i]; i++)
    //     printf("Line [%d]___ %s\n", i, data->file->map->map[i]); 
    if(data->file->map->map == NULL)
        return (1); 
    return (0); 
}
