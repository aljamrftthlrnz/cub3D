
#include "../includes/cub3d.h"

void err_message(char *str)
{
	printf("Error\n%s", str); 
}

int valid_extension (char *str)
{
    if(ft_strlen(str) < 5 || ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4) != 0)
    {
        return (err_message(EXT), 1); 
    }
    return(0); 
}

int	main(int argc, char **argv)
{
	int		error_code;
	t_data	*d;

	error_code = 0; 
	if(argc == 2)
	{
		if(valid_extension(NULL, argv[1]))
			return(1);  
		printf("HELLO\n"); 
		d = (t_data *) malloc(sizeof(t_data));
		if (d == NULL)
			return (1);
		exit(0); 
		init_data(d);
		create_map_for_input_check(d,argv[1]); 
		
		error_code = d->error;
		free_data(d);
	}
	return (error_code);
}