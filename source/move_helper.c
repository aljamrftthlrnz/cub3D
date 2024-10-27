#include "../includes/cub3d.h"

int	corner_in_circle(t_data *d, float y, float x)
{
	float	og_x;
	float	og_y;

	og_x = x;
	og_y = y;
	if (fmodf(y, 1) > 0.5)
		y = ceilf(y);
	else
		y = floorf(y) - 0.001;
	if (fmodf(x, 1) > 0.5)
		x = ceilf(x);
	else
		x = floorf(x) - 0.001;
	if ((d->map->map[(int) og_y][(int) x] == '1' && \
		d->map->map[(int) y][(int) og_x] == '1') \
		|| d->map->map[(int) og_y][(int) og_x] == '1')
	{
		if (point_calc(og_x, og_y, x, y) < 0.1)
			return (1);
	}
	return (0);
}

float	point_calc(float px, float py, float cx, float cy)
{
	float	sq_x;
	float	sq_y;

	sq_x = (px - cx) * (px - cx);
	sq_y = (py - cy) * (py - cy);
	return (sqrtf(sq_x + sq_y));
}
