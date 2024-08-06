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
