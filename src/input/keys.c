/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:00:12 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/08 20:56:48 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(double x, double y, t_app_state *state)
{
	int		map_x;
	int		map_y;
	char	tile;

	if (x < 0 || y < 0)
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_y >= state->map_height)
		return (0);
	if (map_x >= (int)ft_strlen(state->map[map_y]))
		return (0);
	tile = state->map[map_y][map_x];
	return (ft_strchr("0NSEW", tile) != NULL);
}

static int	try_move(t_app_state *state, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	int		moved;

	moved = 0;
	new_x = state->pos_dir.x_pos + move_x;
	new_y = state->pos_dir.y_pos + move_y;
	if (is_walkable(new_x, state->pos_dir.y_pos, state))
	{
		state->pos_dir.x_pos = new_x;
		moved = 1;
	}
	if (is_walkable(state->pos_dir.x_pos, new_y, state))
	{
		state->pos_dir.y_pos = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_player(t_app_state *state, int keycode)
{
	if (keycode == KEY_W)
		return (try_move(state,
				state->pos_dir.x_dir * MOVE_SPEED,
				state->pos_dir.y_dir * MOVE_SPEED));
	if (keycode == KEY_S)
		return (try_move(state,
				-state->pos_dir.x_dir * MOVE_SPEED,
				-state->pos_dir.y_dir * MOVE_SPEED));
	if (keycode == KEY_A)
		return (try_move(state,
				state->pos_dir.y_dir * MOVE_SPEED,
				-state->pos_dir.x_dir * MOVE_SPEED));
	if (keycode == KEY_D)
		return (try_move(state,
				-state->pos_dir.y_dir * MOVE_SPEED,
				state->pos_dir.x_dir * MOVE_SPEED));
	return (0);
}

static void	rotate_view(t_app_state *state, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	sine;
	double	cosine;

	sine = sin(angle);
	cosine = cos(angle);
	old_dir_x = state->pos_dir.x_dir;
	state->pos_dir.x_dir = old_dir_x * cosine
		- state->pos_dir.y_dir * sine;
	state->pos_dir.y_dir = old_dir_x * sine
		+ state->pos_dir.y_dir * cosine;
	old_plane_x = state->pos_dir.x_plane;
	state->pos_dir.x_plane = old_plane_x * cosine
		- state->pos_dir.y_plane * sine;
	state->pos_dir.y_plane = old_plane_x * sine
		+ state->pos_dir.y_plane * cosine;
}

int	on_key_press(int keycode, t_app_state *state)
{
	double	angle;

	if (keycode == KEY_ESC)
	{
		close_app(state);
		return (0);
	}
	angle = 0.0;
	if (keycode == KEY_LEFT)
		angle = -ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		angle = ROT_SPEED;
	if (angle != 0.0)
	{
		rotate_view(state, angle);
		state->needs_redraw = 1;
	}
	else if (move_player(state, keycode))
		state->needs_redraw = 1;
	return (0);
}
