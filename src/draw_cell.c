/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 13:30:16 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/20 13:31:36 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(char c)
{
	if (c == '1')
		return (0x003C3C3C);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x00D8D2C4);
	//if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	//	return (0x00E63946);
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

void	draw_cell(t_app_state *state, int row, int col, int size)
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
			if (y == row * size || y == ((row + 1) * size) - 1 ||
				x == col * size || x == ((col + 1) * size) - 1)
			{
				put_pixel(&state->image, x, y, 0x00333333);
			}
			else
			{
				put_pixel(&state->image, x, y, color);
			}
			x++;
		}
		y++;
	}
}