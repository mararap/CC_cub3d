/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_space(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}

static int	is_identifier(char *line, char *id, int len)
{
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	return (line[len] && ft_isspace(line[len]));
}

int	parser_all_config(t_app_state *state)
{
	return (state->config_flags.no_set && state->config_flags.so_set
		&& state->config_flags.we_set && state->config_flags.ea_set
		&& state->config_flags.f_set && state->config_flags.c_set);
}

static int	parse_texture_id(t_app_state *state, char *line)
{
	if (is_identifier(line, "NO", 2))
		return (parser_set_texture(line + 2, &state->scene.tex_no,
				&state->config_flags.no_set));
	if (is_identifier(line, "SO", 2))
		return (parser_set_texture(line + 2, &state->scene.tex_so,
				&state->config_flags.so_set));
	if (is_identifier(line, "WE", 2))
		return (parser_set_texture(line + 2, &state->scene.tex_we,
				&state->config_flags.we_set));
	if (is_identifier(line, "EA", 2))
		return (parser_set_texture(line + 2, &state->scene.tex_ea,
				&state->config_flags.ea_set));
	return (-1);
}

int	parser_parse_config(t_app_state *state, char *line)
{
	int	result;

	line = skip_space(line);
	result = parse_texture_id(state, line);
	if (result != -1)
		return (result);
	if (is_identifier(line, "F", 1))
		return (parser_set_color(line + 1, &state->scene.color_floor,
				&state->config_flags.f_set));
	if (is_identifier(line, "C", 1))
		return (parser_set_color(line + 1, &state->scene.color_ceil,
				&state->config_flags.c_set));
	return (parser_error("Invalid scene configuration line"));
}
