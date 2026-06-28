/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 12:34:03 by jatanaso          #+#    #+#             */
/*   Updated: 2026/06/28 12:34:03 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_image_buffer *image, int x, int y, int color)
{
	int		bpp;
	char	*ptr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	bpp = image->bits_per_pixel / 8;
	ptr = image->pixels + y * image->line_stride + x * bpp;
	*(unsigned int *)ptr = (unsigned int)color;
}

static int	get_map_width(t_app_state *state)
{
	int	width;
	int	row;
	int	len;

	width = 0;
	row = 0;
	while (row < state->map_height)
	{
		len = (int)ft_strlen(state->map[row]);
		if (len > width)
			width = len;
		row++;
	}
	return (width);
}

static int	get_cell_size(t_app_state *state, int map_width)
{
	int	cell_w;
	int	cell_h;

	if (map_width == 0 || state->map_height == 0)
		return (1);
	cell_w = WINDOW_WIDTH / map_width;
	cell_h = WINDOW_HEIGHT / state->map_height;
	if (cell_w < 1)
		cell_w = 1;
	if (cell_h < 1)
		cell_h = 1;
	if (cell_w < cell_h)
		return (cell_w);
	return (cell_h);
}

static int	get_color(char c)
{
	if (c == '1')
		return (0x003C3C3C);
	if (c == '0')
		return (0x00D8D2C4);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x00E63946);
	return (0x00111111);
}

static char	get_map_cell(t_app_state *state, int row, int col)
{
	if (row >= state->map_height)
		return (' ');
	if (col >= (int)ft_strlen(state->map[row]))
		return (' ');
	return (state->map[row][col]);
}

static void	fill_image(t_image_buffer *image, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_cell(t_app_state *state, int row, int col, int size)
{
	int	x;
	int	y;
	int	color;

	color = get_color(get_map_cell(state, row, col));
	y = row * size;
	while (y < (row + 1) * size)
	{
		x = col * size;
		while (x < (col + 1) * size)
		{
			put_pixel(&state->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_frame(t_app_state *state)
{
	int	row;
	int	col;
	int	width;
	int	size;

	fill_image(&state->image, 0x00111111);
	width = get_map_width(state);
	size = get_cell_size(state, width);
	row = 0;
	while (row < state->map_height)
	{
		col = 0;
		while (col < width)
		{
			draw_cell(state, row, col, size);
			col++;
		}
		row++;
	}
}
