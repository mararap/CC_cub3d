/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/23 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_space(char **value)
{
	while (**value && ft_isspace(**value))
		(*value)++;
}

static int	parse_component(char **value, int *component)
{
	int	number;

	skip_space(value);
	if (!ft_isdigit(**value))
		return (0);
	number = 0;
	while (ft_isdigit(**value))
	{
		number = number * 10 + (**value - '0');
		if (number > 255)
			return (0);
		(*value)++;
	}
	skip_space(value);
	*component = number;
	return (1);
}

static int	parse_rgb(char *value, int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!parse_component(&value, &rgb[i]))
			return (0);
		if (i < 2 && *value != ',')
			return (0);
		if (i < 2)
			value++;
		i++;
	}
	return (*value == '\0');
}

int	parser_set_color(char *value, int *slot, int *is_set)
{
	int	rgb[3];

	if (*is_set)
		return (report_error("Duplicate color identifier"));
	if (!parse_rgb(value, rgb))
		return (report_error("Color must contain three values from 0 to 255"));
	*slot = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	*is_set = 1;
	return (1);
}
