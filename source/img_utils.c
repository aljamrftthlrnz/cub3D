/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:53:08 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/27 16:53:09 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	img_get_pos(t_image *img, int x, int y)
{
	int	pixel_molecule;
	int	position;

	pixel_molecule = img->bits_per_pixel / 8;
	if (x > img->width || y > img->height)
	{
		return (-1);
	}
	position = y * img->size_line;
	position = position + (x * pixel_molecule);
	return (position);
}

// takes coordinates and puts color accordingly on coordinates of img-address
// careful of segfault when coordinates are bigger than size of image
void	pixel_to_img(t_image *img, int x, int y, int *rgb)
{
	int	position;

	position = img_get_pos(img, x, y);
	if (position < 0)
	{
		return ;
	}
	img->img_adr[position++] = rgb[0];
	img->img_adr[position++] = rgb[1];
	img->img_adr[position] = rgb[2];
}

// takes pointer to image struct, height 
void	fill_color_img(t_image *image, int *rgb)
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

//destination image, source image, destination position, source position
void	copy_pos_to_img(t_image *d_img, t_image *s_img, int d_pos, int s_pos)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		d_img->img_adr[d_pos++] = s_img->img_adr[s_pos++];
		i++;
	}
}
