/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 00:00:00 by marapovi          #+#    #+#             */
/*   Updated: 2026/09/19 18:19:53 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns the value for one single pixel of the texture:
// It calculates the bytes per pixel by dividing bits_per_pixel by 8, because
// memory is addressed in bytes, not bits. In normal textures, each pixel is
// usually 32 bits (4 bytes). To move from pixel x to pixel x + 1, we need to
// move 'bits_per_pixel / 8' forward (4 in case of 32 bits per pixel).
// Before computing the value of the pixel, the function checks if the pixel
// is actually inside the borders of the texture.
// texture->pixels      ... pointer to start of texture data in memory
// texture->line_stride ... how many bytes to skip to get to the next row
// 'y * texture->line_stride' gives us the byte offset for row y.
// 'x * bytes_per_pixel' gives us the offset within that row to column x.
static unsigned int	get_texture_pixel(t_image_buffer *texture, int x, int y)
{
	char	*pixel;
	int		bytes_per_pixel;

	bytes_per_pixel = texture->bits_per_pixel / 8;
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->pixels + y * texture->line_stride + x * bytes_per_pixel;
	return (*(unsigned int *)pixel);
}

// Maps texture pixels vertically to screen pixels and handles scaling:
// step             ... a scaling factor for the texture->height:
//                      If the wall is taller than the texture, multiple
//                      vertical pixels will use the same texture row;
//                      If the wall is shorter, fewer (or only one) vertical
//                      pixel will use one texture row's value.
// texture_position ... which row of the texture to start from.
// Starting from texture_position, it loops through the texture column
// vertically using texture_y, while protecting against invalid reads.
// It calls get_texture_pixel to get the color of the texture in position x
// and y and write it to the image buffer with put_pixel. 
void	draw_textured_wall(t_app_state *state, t_draw_column *column,
		int screen_x)
{
	double			step;
	double			texture_position;
	int				texture_y;
	int				y;
	unsigned int	color;

	step = (double)column->texture->height / column->line_height;
	texture_position = (column->draw_start - WINDOW_HEIGHT / 2.0
			+ column->line_height / 2.0) * step;
	y = column->draw_start;
	while (y <= column->draw_end)
	{
		texture_y = (int)texture_position;
		if (texture_y < 0)
			texture_y = 0;
		if (texture_y >= column->texture->height)
			texture_y = column->texture->height - 1;
		color = get_texture_pixel(column->texture, column->tex_x, texture_y);
		put_pixel(&state->image, screen_x, y, color);
		texture_position += step;
		y++;
	}
}
