/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_space(char *value)
{
	while (*value && ft_isspace(*value))
		value++;
	return (value);
}

static int	path_is_valid(char *path)
{
	char	byte;
	int		fd;
	int		read_result;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	read_result = read(fd, &byte, 1);
	if (close(fd) == -1)
		return (0);
	return (read_result >= 0);
}

static char	*copy_path(char *value)
{
	char	*end;
	char	*path;
	char	saved;

	value = skip_space(value);
	end = value;
	while (*end && !ft_isspace(*end))
		end++;
	if (end == value || *skip_space(end) != '\0')
		return (NULL);
	saved = *end;
	*end = '\0';
	path = ft_strdup(value);
	*end = saved;
	return (path);
}

int	parser_set_texture(char *value, char **slot, int *is_set)
{
	char	*path;

	if (*is_set)
		return (parser_error("Duplicate texture identifier"));
	path = copy_path(value);
	if (!path)
		return (parser_error("Texture requires exactly one path"));
	if (!path_is_valid(path))
	{
		free(path);
		return (parser_error("Texture path is not a readable file"));
	}
	*slot = path;
	*is_set = 1;
	return (1);
}
