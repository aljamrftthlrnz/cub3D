
#include "../includes/cub3d.h"

static void process_file_to_stash(int *i, char *stash, char *line)
{
    int j; 
    j = 0;
    while(line && line[j] != '\n' && line[j] != '\0')
        stash[(*i)++] = line[j++]; 
    if (line[j] == '\n')
        stash[(*i)++] = '\n'; 
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

void get_longest_line(t_data *d, char *argv)
{
    int fd; 
    char *line; 
    int max;

    fd = open(argv, O_RDONLY); 
    if(fd < 0)
        d->error = FD_ERROR;
    line = get_next_line(fd); 
    if(!line)
        d->error = MAP_EMPTY;  
    max = ft_strlen(line); 
    while(line != NULL)
    {
        free(line); 
        line = get_next_line(fd); 
        if((size_t)max < ft_strlen(line))
            max = ft_strlen(line); 
    }
    d->x_file = max; 
}

void get_length_of_file(t_data *d, char *argv)
{
    int fd; 
    char *line; 
    int count; 
    t_file *file; 

    file = d->file; 
    fd = open(argv, O_RDONLY); 
    if(fd < 0)
        d->error = FD_ERROR; 
    count = 0; 
    line = get_next_line(fd); 
    if(!line)
        d->error = MAP_EMPTY; 
    while (line != NULL)
    {
        count++; 
        free(line); 
        line = get_next_line(fd); 
    }
    d->y_file = count; 
    close(fd); 
}

void create_map_for_input_check(t_data *d, char *argv)
{
    get_length_of_file(d, argv);
    get_longest_line(d, argv);  
    create_info_array(d, argv);
    if(d->error != 0)
    {
        //exit out program display error
        return ; 
    }
}
