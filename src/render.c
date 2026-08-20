/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 13:16:54 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/20 17:46:15 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_cell_size(t_app_state *state)
{
	int	cell_w;
	int	cell_h;

	if (state->map_width == 0 || state->map_height == 0)
		return (1);
	cell_w = WINDOW_WIDTH / state->map_width;
	cell_h = WINDOW_HEIGHT / state->map_height;
	if (cell_w < 1)
		cell_w = 1;
	if (cell_h < 1)
		cell_h = 1;
	if (cell_w < cell_h)
		return (cell_w);
	return (cell_h);
}

void	render_frame(t_app_state *state)
{
	int		row;
	int		col;
	int		size;

	fill_image(&state->image, 0x00111111);
	size = get_cell_size(state);
	row = 0;
	while (row < state->map_height)
	{
		col = 0;
		while (col < state->map_width)
		{
			draw_cell(state, row, col, size);
			col++;
		}
		row++;
	}
	draw_player(state, size);
	cast_ray_fan(state, size);
}