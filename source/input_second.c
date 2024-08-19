#include "../includes/cub3d.h"

int check_multiple_seperators(char *str)
{
    int sep;
    int i;

    i = 0; 
    sep = 0;
    while (str[i]) 
    {
        if (str[i] == ',') 
        {
            if (sep)
                return (1);
            sep = 1;
        } else 
            sep = 0;
        i++;
    }
    return (sep);
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
        return(1); 
    return (0); 
}
