#include "../includes/cub3d.h"

int	img_get_pos(t_image *img, int x, int y)
{
	int pixel_molecule = img->bits_per_pixel / 8;
	int position;

	if (x > img->width || y > img->height)
	{
		// printf("pixel_to_img: entered coordinates are outside of image x=%d y=%d\n", x, y);
		return (-1);
	}
	position = y * img->size_line;// * pixel_molecule;
	// printf("position: %d\n", position);
	position = position + (x * pixel_molecule);
	return (position);
}

// takes coordinates and puts color accordingly on coordinates of img-address
// careful of segfault when coordinates are bigger than size of image
void	pixel_to_img(t_image *img, int x, int y, int *rgb)
{
	int pixel_molecule = img->bits_per_pixel / 8;
	int position;

	if (x >= img->width || y >= img->height)
	{
		// printf("pixel_to_img: entered coordinates are outside of image");
		return ;
	}
	position = y * img->size_line;// * pixel_molecule;
	// printf("position: %d\n", position);
	position = position + (x * pixel_molecule);
	// printf("position2: %d\n", position);
	// if ((int) ft_strlen(img->img_adr) < position)
	// 	return;
	img->img_adr[position++] = rgb[0];
	img->img_adr[position++] = rgb[1];
	img->img_adr[position] = rgb[2];
}


// takes pointer to image struct, height 
void fill_color_img(t_image *image, int *rgb)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < image->height)
	{
		pixel_to_img(image, x++, y, rgb);
		if (x >= image->width)
		{
			x = 0;
			y++;
		}
	}
}