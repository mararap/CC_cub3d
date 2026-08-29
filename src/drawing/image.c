/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:52:40 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/29 00:00:00 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_image_buffer *image, int x, int y, int color)
{
	int		bytes_per_pixel;
	char	*pixel;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	bytes_per_pixel = image->bits_per_pixel / 8;
	pixel = image->pixels + y * image->line_stride
		+ x * bytes_per_pixel;
	*(unsigned int *)pixel = (unsigned int)color;
}

void	redraw_frame(t_app_state *state)
{
	render_frame(state);
	mlx_put_image_to_window(state->mlx, state->window,
		state->image.handle, 0, 0);
	state->needs_redraw = 0;
}
