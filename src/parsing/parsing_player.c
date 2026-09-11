/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_direction(t_pos_dir *pos, char direction)
{
	pos->x_dir = (direction == 'E') - (direction == 'W');
	pos->y_dir = (direction == 'S') - (direction == 'N');
	pos->x_plane = 0.66 * ((direction == 'N') - (direction == 'S'));
	pos->y_plane = 0.66 * ((direction == 'E') - (direction == 'W'));
}

int	parser_find_player(t_app_state *state)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (++y < state->map_height)
	{
		x = -1;
		while (state->map[y][++x])
		{
			if (ft_strchr("NSEW", state->map[y][x]))
			{
				count++;
				state->pos_dir.x_pos = x + 0.5;
				state->pos_dir.y_pos = y + 0.5;
				set_direction(&state->pos_dir, state->map[y][x]);
			}
		}
	}
	return (count);
}
