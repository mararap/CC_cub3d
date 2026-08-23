/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 12:51:43 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/20 17:44:38 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// Juliyan

// handle map

/*• Your program must take as a first argument a scene description file with the .cub
extension.
◦ The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.
This is a simple valid map:
111111
100101
101001
1100N1
111111
◦ The map must be closed/surrounded by walls, if not the program must return
an error.
◦ Except for the map content, each type of element can be separated by one or
more empty lines.
◦ Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
◦ Except for the map, each type of information from an element can be separated
by one or more spaces.
◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.*/

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_newline(char *line)
{
	int	len;

	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	is_map_char(char c)
{
	return (ft_strchr("01NSEW ", c) != NULL);
}

static int	looks_like_map_line(char *line)
{
	int	i;
	int	has_content;

	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]))
			return (0);
		if (ft_strchr("01NSEW", line[i]))
			has_content = 1;
		i++;
	}
	return (has_content);
}

static void check_first_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
		{
			write(2, "Error\nFirst and last map rows must contain only '1'\n", 53);
			exit(1);
		}
		i++;
	}
}

static void	check_map_line(char *line)
{
	int	i;
	int	first;
	int	last;

	first = 0;
	while (line[first] == ' ')
		first++;
	last = (int)ft_strlen(line) - 1;
	while (last >= 0 && line[last] == ' ')
		last--;
	if (last < first || line[first] != '1')
		return (write(2, "Error\nMap row must start with 1\n", 32), exit(1));
	if (line[last] != '1')
		return (write(2, "Error\nMap row must end with 1\n", 30), exit(1));
	i = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]))
			return (write(2, "Error\nInvalid map character\n", 28), exit(1));
		i++;
	}
}

static void	add_map_line(t_app_state *state, char *line)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(state->map_height + 2, sizeof(char *));
	if (!new_map)
		return (perror("Error\nmalloc"), exit(1));
	i = 0;
	while (i < state->map_height)
	{
		new_map[i] = state->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
		return (perror("Error\nmalloc"), exit(1));
	if ((int)ft_strlen(line) > state->map_width)
		state->map_width = (int)ft_strlen(line);
	free(state->map);
	state->map = new_map;
	state->map_height++;
}

static void	handle_config_line(t_app_state *state, char* line)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (state->textures.no_set)
			return (write(2, "Error\nDuplicate NO texture\n", 27), exit(1));
		state->textures.no_set = 1;
		set_north_texture(line);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (state->textures.so_set)
			return (write(2, "Error\nDuplicate SO texture\n", 27), exit(1));
		state->textures.so_set = 1;
		set_south_texture(line);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (state->textures.we_set)
			return (write(2, "Error\nDuplicate WE texture\n", 27), exit(1));
		state->textures.we_set = 1;
		set_west_texture(line);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (state->textures.ea_set)
			return (write(2, "Error\nDuplicate EA texture\n", 27), exit(1));
		state->textures.ea_set = 1;
		set_east_texture(line);
	}
	else if (line[0] == 'F')
	{
		if (state->textures.f_set)
			return (write(2, "Error\nDuplicate F texture\n", 26), exit(1));
		state->textures.f_set = 1;
		set_floor_color(line);
	}
	else if (line[0] == 'C')
	{
		if (state->textures.c_set)
			return (write(2, "Error\nDuplicate C texture\n", 26), exit(1));
		state->textures.c_set = 1;
		set_ceiling_color(line);
	}
	else
		return (write(2, "Error\nInvalid cub file line\n", 28), exit(1));
}

static void	trim_map_line(char *line)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	while (line[start] && ft_isspace(line[start]))
		start++;

	end = ft_strlen(line);
	while (end > start && ft_isspace(line[end - 1]))
		end--;

	i = 0;
	while (start < end)
		line[i++] = line[start++];
	line[i] = '\0';
}

static void	read_cub_lines(int fd, t_app_state *state)
{
	char	*line;
	int		in_map;

	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (!is_empty_line(line))
		{
			if (!in_map && looks_like_map_line(line))
			{
				if (!state->textures.no_set || !state->textures.so_set ||
					!state->textures.we_set || !state->textures.ea_set ||
					!state->textures.f_set || !state->textures.c_set)
				{
					write(2, "Error\nMissing configuration\n", 28);
					free(line);
					ft_error_exit();
				}
				in_map = 1;				
			}
			if (in_map)
			{
				trim_map_line(line);
				check_map_line(line);
				add_map_line(state, line);
			}
			else
			{
				trim_map_line(line);
				handle_config_line(state, line);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}

static int is_open_tile(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static void check_map_closed(char **map, int height)
{
	int x;
	int y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (is_open_tile(map[y][x]))
			{
				if (x == 0 || map[y][x - 1] == ' ' || map[y][x + 1] == '\0' 
					|| map[y][x + 1] == ' ' || y == 0 || y == height - 1
					|| x >= (int)ft_strlen(map[y - 1]) || map[y - 1][x] == ' ' 
					|| x >= (int)ft_strlen(map[y + 1]) || map[y + 1][x] == ' ')
				{
					write(2, "Error \nMap is not closed\n", 24);
					exit(1);
				}
			}
			x++;
		}
		y++;
	}
}

static void check_single_player(char **map, int height, t_app_state *state)
{
	int x;
	int y;
	int player_count;

	y = 0;
	player_count = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || 
				map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (map[y][x] == 'N')
				{
					state->pos_dir.x_dir = 0;
					state->pos_dir.y_dir = -1;
					state->pos_dir.x_plane = 0.66;
					state->pos_dir.y_plane = 0.0;
				}
				if (map[y][x] == 'S')
				{
					state->pos_dir.x_dir = 0;
					state->pos_dir.y_dir = 1;
					state->pos_dir.x_plane = -0.66;
					state->pos_dir.y_plane = 0.0;
				}
				if (map[y][x] == 'E')
				{	
					state->pos_dir.x_dir = 1;
					state->pos_dir.y_dir = 0;
					state->pos_dir.x_plane = 0.0;
					state->pos_dir.y_plane = 0.66;
				}
				if (map[y][x] == 'W')
				{
					state->pos_dir.x_dir = -1;
					state->pos_dir.y_dir = 0;
					state->pos_dir.x_plane = 0.0;
					state->pos_dir.y_plane = -0.66;					
				}
				player_count++;
				state->pos_dir.x_pos = (double)x + 0.5;
				state->pos_dir.y_pos = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		write(2, "Error\nMap must contain exactly one player\n", 42);
		exit(1);
	}
}

int	parse_map(int argc, char **argv, t_app_state *state)
{
	int	fd;

	if (argc != 2)
		return (write(2, "Error\nNo scene file specified\n", 30), exit(1), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror("Error\nopen"), exit(1), 0);
	//state->map = NULL;
	//state->map_height = 0;
	read_cub_lines(fd, state);
	close(fd);
	if (state->map_height == 0)
		return (write(2, "Error\nMissing map\n", 18), exit(1), 0);
	check_first_last_line(state->map[0]);
	check_first_last_line(state->map[state->map_height - 1]);
	check_map_closed(state->map, state->map_height);
	check_single_player(state->map, state->map_height, state);
	return (1);
}
