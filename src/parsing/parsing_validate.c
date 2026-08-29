/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	map_at(t_app_state *state, int y, int x)
{
	if (y < 0 || y >= state->map_height || x < 0)
		return (' ');
	if (x >= (int)ft_strlen(state->map[y]))
		return (' ');
	return (state->map[y][x]);
}

static int	is_open_tile(char tile)
{
	return (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W');
}

static int	validate_closed(t_app_state *state)
{
	int	x;
	int	y;

	y = -1;
	while (++y < state->map_height)
	{
		x = -1;
		while (state->map[y][++x])
		{
			if (is_open_tile(state->map[y][x])
				&& (map_at(state, y - 1, x) == ' '
					|| map_at(state, y + 1, x) == ' '
					|| map_at(state, y, x - 1) == ' '
					|| map_at(state, y, x + 1) == ' '))
				return (report_error("Map is not closed by walls"));
		}
	}
	return (1);
}

int	parser_validate_map(t_app_state *state)
{
	if (!validate_closed(state))
		return (0);
	if (parser_find_player(state) != 1)
		return (report_error("Map must contain exactly one player"));
	return (1);
}
