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

int file_length(char **arr)
{
    int i; 

    i = 0; 
    while(arr[i] != NULL)
        i++; 
    return (i); 
}
