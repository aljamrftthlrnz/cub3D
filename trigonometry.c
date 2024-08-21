#include "cub3d.h"

int	main()
{
	int	angle = 30;
	float	radian = angle * 0.017453;
	// float	sinus = 
	int	adjacent = 1;

	float	opposite;
	float	hypothenuse;


	while (adjacent < 130)
	{
		printf("angle: %d\nradian: %f\n", angle, radian);

		opposite = tanf(radian) * adjacent;
		hypothenuse = opposite / sinf(radian);

		printf("adjacent: %d\nopposite: %f\nhypothenuse: %f\n", adjacent, opposite, hypothenuse);
		printf("---\n");

		adjacent += 30;
	}

	return 0;
}