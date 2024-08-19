
#include "../includes/cub3d.h"

int err_free_message(t_data *data, int error_code)
{
	printf("Error\n");
	if(error_code == ARG_FAIL)
		printf("%s", ARG);
	else if (error_code == EXT_ERROR)
		printf("%s", EXT); 
	else if (error_code == ALLOC_FAIL)
		printf("%s", ALLOC_F);
	else if (error_code == IDENT_W)
		printf("%s", IDENT);
	else if (error_code == PERS_D)
		printf("%s", PERS);
	else if (error_code == PERS_M)
		printf("%s", PERS_MI);
	else if (error_code == FL_CEIL_M)
		printf("%s", FL_CE_MISS);
	else if (error_code == FL_CEIL_D)
		printf("%s", FLOOR_CEILING);
	else if (error_code == RGB_W)
		printf("%s", RGB_WRO);
	else if (error_code == ORDER)
		printf("%s", ORDER_W);
	else if (error_code == MISSING_MAP)
		printf("%s", MISS_MAP); 
	free_data(data); 
	exit (error_code);  
}

int arguments_and_extension (int argc, char *str, int *error)
{
    if(argc != 2)
	{
		*error = ARG_FAIL;
		return(*error); 
	}
	else if (ft_strlen(str) < 5 || ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4) != 0)
	{
		*error = EXT_ERROR; 
		return(*error); 
	}
	return(0); 
}

int	main(int argc, char **argv)
{
	int		error_code;
	t_data	*d;

	error_code = 0; 
	if(arguments_and_extension(argc,argv[1], &error_code))
		err_free_message(NULL, error_code); 
	d = (t_data *) malloc(sizeof(t_data));
	if (d == NULL)
		err_free_message(NULL, ALLOC_FAIL); 
	init_data(d);
	create_map_for_input_check(d,argv[1]);
	error_code = d->error;
	free_data(d);
	return(error_code);
}
