#include "../includes/cub3d.h"

int is_c_space(char c)
{
    if(c == ' ')
        return(1); 
    return(0); 
}

int is_space(char *line)
{
    int i;

    i = 0; 
    while(line[i])
    {
        if(line[i] != ' ')
            return(1); 
        i++;
    }
    return (0); 
}

int is_character(char c)
{
    if(c == 'N' || c == 'W' || c == 'S' || c == 'E')
        return (1); 
    return (0); 
}

int is_wall_space(char c)
{
    if(c == '0' || c == '1')
        return(1); 
    return(0); 
}

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

int file_length(char **arr)
{
    int i; 

    i = 0; 
    while(arr[i] != NULL)
        i++; 
    return (i); 
}

void process_map(t_data *data)
{
    
}

int check_order_of_file(t_data *data)
{
    int length;
    int j; 

    length = file_length(data->file_arr); 
    j = length - 1; 
    while(!is_space(data->file_arr[j]))
        j--; 
    if(is_map_line(data->file_arr[j]))
        err_free_message (data, ORDER); 
    else 
        process_map(data); 
    return (0); 
}