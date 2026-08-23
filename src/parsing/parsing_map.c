/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parser_is_blank(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

void	parser_strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len && line[len - 1] == '\n')
		line[--len] = '\0';
	if (len && line[len - 1] == '\r')
		line[len - 1] = '\0';
}

static int	is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	parser_is_map_line(char *line)
{
	int	has_tile;

	has_tile = 0;
	while (*line)
	{
		if (!is_map_char(*line))
			return (0);
		if (*line != ' ')
			has_tile = 1;
		line++;
	}
	return (has_tile);
}

int	parser_add_map_line(t_app_state *state, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (line[i])
		if (!is_map_char(line[i++]))
			return (parser_error("Map contains an invalid character"));
	new_map = ft_calloc(state->map_height + 2, sizeof(char *));
	if (!new_map)
		return (parser_error("Memory allocation failed"));
	i = -1;
	while (++i < state->map_height)
		new_map[i] = state->map[i];
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
		return (free(new_map), parser_error("Memory allocation failed"));
	free(state->map);
	state->map = new_map;
	state->map_height++;
	if ((int)ft_strlen(line) > state->map_width)
		state->map_width = (int)ft_strlen(line);
	return (1);
}
