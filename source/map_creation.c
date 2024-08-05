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

void create_info_array(t_data *d, char *argv)
{
    char *stash; 
    char *line; 
    int i; 
    int fd; 

    i = 0; 
    fd = open(argv, O_RDONLY); 
    if(fd < 0)
        d->error = FD_ERROR;
    line = get_next_line(fd);
    stash = ft_calloc(sizeof(char), (d->x_file * d->y_file) + 1); 
    if(!stash)
       d->error = MAP_EMPTY; 
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
    printf("Longest line is: %d\n", max);
    printf("Length of Line is: %d\n", count); 
    d->y_file = count;  
    d->x_file = max; 
    close(fd); 
}

// void get_length_of_file(t_data *d, char *argv)
// {
//     int fd; 
//     char *line; 
//     int count; 
//     t_file *file; 

//     file = d->file; 
//     fd = open(argv, O_RDONLY); 
//     if(fd < 0)
//         d->error = FD_ERROR; 
//     count = 0; 
//     line = get_next_line(fd); 
//     if(!line)
//         d->error = MAP_EMPTY; 
//     while (line != NULL)
//     {
//         count++; 
//         free(line); 
//         line = get_next_line(fd); 
//     }
//     printf("Length of Line is: %d\n", count); 
//     d->y_file = count; 
//     close(fd); 
// }

void create_map_for_input_check(t_data *d, char *argv)
{
    get_dimensions_of_file(d, argv); 
    create_info_array(d, argv);
    for (int i = 0; d->file_arr[i]; i++)
        printf("Line (%d): %s\n", i, d->file_arr[i]); 
    if(d->error != 0)
    {
        //exit out program display error
        return ; 
    }
}
