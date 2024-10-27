#include "../includes/cub3d.h"

void	print_error_3(int error_code)
{
	if (error_code == MLXIMG)
		ft_putstr_fd(MLXIMG_M, 2);
	else if (error_code == MLXSIZ)
		ft_putstr_fd(MLXSIZ_M, 2);
	else if (error_code == RGB_MI)
		ft_putstr_fd(RGB_M, 2);
}

void print_error_3(int error_code)
{
	if (error_code == MLXSIZ)
		ft_putstr_fd(MLXSIZ_M, 2);
	else if (error_code == RGB_MI)
		ft_putstr_fd(RGB_M, 2);
	else if (error_code == TXT_WRONG)
		ft_putstr_fd(TXT_WRO, 2);
}

void	print_error_2(int error_code)
{
	if (error_code == ORDER)
		ft_putstr_fd(ORDER_W, 2);
	else if (error_code == MISSING_MAP)
		ft_putstr_fd(MISS_MAP, 2);
	else if (error_code == FILE_EMPTY)
		ft_putstr_fd(FILE_EMPT, 2);
	else if (error_code == ORDER_ID)
		ft_putstr_fd(ORDER_I, 2);
	else if (error_code == EMPTY_LINES)
		ft_putstr_fd(EMPTY_L, 2);
	else if (error_code == BORDER_M)
		ft_putstr_fd(BORDER, 2);
	else if (error_code == PLAYER_W)
		ft_putstr_fd(PLAYER, 2);
	else if (error_code == SPACE_PROT)
		ft_putstr_fd(SPACE, 2);
	else if (error_code == MLXIN)
		ft_putstr_fd(MLXIN_M, 2);
	else if (error_code == MLXWI)
		ft_putstr_fd(MLXWI_M, 2);
	else
		print_error_3(error_code);
}

void	print_error(int error_code)
{
	ft_putstr_fd("Error\n", 2);
	if (error_code == ARG_FAIL)
		ft_putstr_fd(ARG, 2);
	else if (error_code == EXT_ERROR)
		ft_putstr_fd(EXT, 2);
	else if (error_code == ALLOC_FAIL)
		ft_putstr_fd(ALLOC_F, 2);
	else if (error_code == IDENT_W)
		ft_putstr_fd(IDENT, 2);
	else if (error_code == PERS_D)
		ft_putstr_fd(PERS, 2);
	else if (error_code == PERS_M)
		ft_putstr_fd(PERS_MI, 2);
	else if (error_code == FL_CEIL_M)
		ft_putstr_fd(FL_CE_MISS, 2);
	else if (error_code == FL_CEIL_D)
		ft_putstr_fd(FLOOR_CEILING, 2);
	else if (error_code == RGB_W)
		ft_putstr_fd(RGB_WRO, 2);
	else
		print_error_2(error_code);
}

int	err_free_message(t_data *d, int error_code)
{
	if (error_code != 0)
		print_error(error_code);
	free_data(d);
	exit (error_code);
}
