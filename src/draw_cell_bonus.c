/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/28 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_X 16
#define MINIMAP_Y 16
#define MINIMAP_MAX_WIDTH 320
#define MINIMAP_MAX_HEIGHT 240

static int	get_color(char cell)
{
	if (cell == '1')
		return (0x003C3C3C);
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W')
		return (0x00D8D2C4);
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

int	minimap_cell_size(t_app_state *state)
{
	int	cell_width;
	int	cell_height;

	if (state->map_width == 0 || state->map_height == 0)
		return (1);
	cell_width = MINIMAP_MAX_WIDTH / state->map_width;
	cell_height = MINIMAP_MAX_HEIGHT / state->map_height;
	if (cell_width < 1)
		cell_width = 1;
	if (cell_height < 1)
		cell_height = 1;
	if (cell_width < cell_height)
		return (cell_width);
	return (cell_height);
}

static int	is_border(int position, int start, int size)
{
	return (position == start || position == start + size - 1);
}

void	draw_minimap_cell(t_app_state *state, int row, int col, int size)
{
	int	x;
	int	y;
	int	color;

	color = get_color(get_map_cell(state, row, col));
	y = MINIMAP_Y + row * size;
	while (y < MINIMAP_Y + (row + 1) * size)
	{
		x = MINIMAP_X + col * size;
		while (x < MINIMAP_X + (col + 1) * size)
		{
			if (is_border(y, MINIMAP_Y + row * size, size)
				|| is_border(x, MINIMAP_X + col * size, size))
				put_pixel(&state->image, x, y, 0x00333333);
			else
				put_pixel(&state->image, x, y, color);
			x++;
		}
		y++;
	}
}
