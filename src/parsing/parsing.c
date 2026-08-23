/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub_extension(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len <= 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

static void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static int	consume_line(t_app_state *state, char *line, int *in_map)
{
	if (!*in_map && parser_is_map_line(line))
	{
		if (!parser_all_config(state))
			return (parser_error("Map appears before complete configuration"));
		*in_map = 1;
	}
	if (*in_map)
		return (parser_add_map_line(state, line));
	return (parser_parse_config(state, line));
}

static int	read_scene(int fd, t_app_state *state)
{
	char	*line;
	int		in_map;
	int		map_ended;
	int		ok;

	in_map = 0;
	map_ended = 0;
	ok = 1;
	line = get_next_line(fd);
	while (line && ok)
	{
		parser_strip_newline(line);
		if (in_map && line[0] == '\0')
			map_ended = 1;
		else if (map_ended && !parser_is_blank(line))
			ok = parser_error("The map must be the last file element");
		else if (!parser_is_blank(line) || in_map)
			ok = consume_line(state, line, &in_map);
		free(line);
		if (ok)
			line = get_next_line(fd);
	}
	if (!ok)
		drain_gnl(fd);
	return (ok);
}

int	parse_map(int argc, char **argv, t_app_state *state)
{
	int	fd;
	int	ok;

	if (argc != 2)
		return (parser_error("Expected exactly one .cub scene file"));
	if (!has_cub_extension(argv[1]))
		return (parser_error("Scene file must have a .cub extension"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (parser_error("Cannot open scene file"));
	ok = read_scene(fd, state);
	if (close(fd) == -1 && ok)
		ok = parser_error("Cannot close scene file");
	if (ok && !parser_all_config(state))
		ok = parser_error("Missing scene configuration");
	if (ok && state->map_height == 0)
		ok = parser_error("Missing map");
	if (ok)
		ok = parser_validate_map(state);
	return (ok);
}
