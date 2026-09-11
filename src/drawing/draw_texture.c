/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 00:00:00 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/29 00:00:00 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_texture_pixel(t_image_buffer *texture,
		int x, int y)
{
	char	*pixel;
	int		bytes_per_pixel;

	bytes_per_pixel = texture->bits_per_pixel / 8;
	pixel = texture->pixels + y * texture->line_stride
		+ x * bytes_per_pixel;
	return (*(unsigned int *)pixel);
}

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
		texture_position += step;
		color = get_texture_pixel(column->texture, column->tex_x, texture_y);
		put_pixel(&state->image, screen_x, y, color);
		y++;
	}
}
