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
// handle keys/movement

/*
◦ The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
◦ The W, A, S, and D keys must allow you to move the point of view through
the maze.
◦ Pressing ESC must close the window and quit the program cleanly.
◦ Clicking on the red cross on the window’s frame must close the window and
quit the program cleanly.*/

int	on_key_press(int keycode, t_app_state *state)
{
	double	old_xdir;
	double	old_xplane;
	int 	changed;
	
	changed = 0;
	if (keycode == KEY_ESC)
		return (on_close(state));
	if (keycode == KEY_W)
	{
		state->pos_dir.x_pos += state->pos_dir.x_dir * MOVE_SPEED;
		state->pos_dir.y_pos += state->pos_dir.y_dir * MOVE_SPEED;
		changed = 1;
	}
	if (keycode == KEY_S)
	{
		state->pos_dir.x_pos -= state->pos_dir.x_dir * MOVE_SPEED;
		state->pos_dir.y_pos -= state->pos_dir.y_dir * MOVE_SPEED;
		changed = 1;
	}
	if (keycode == KEY_A)
	{
		state->pos_dir.x_pos += state->pos_dir.y_dir * MOVE_SPEED;
		state->pos_dir.y_pos -= state->pos_dir.x_dir * MOVE_SPEED;
		changed = 1;
	}
	if (keycode == KEY_D)
	{
		state->pos_dir.x_pos -= state->pos_dir.y_dir * MOVE_SPEED;
		state->pos_dir.y_pos += state->pos_dir.x_dir * MOVE_SPEED;
		changed = 1;
	}
	if (keycode == KEY_LEFT)
	{
		old_xdir = state->pos_dir.x_dir;
		state->pos_dir.x_dir = old_xdir * cos(-ROT_SPEED) - state->pos_dir.y_dir * sin(-ROT_SPEED);
		state->pos_dir.y_dir = old_xdir * sin(-ROT_SPEED) + state->pos_dir.y_dir * cos(-ROT_SPEED);
		old_xplane = state->pos_dir.x_plane;
		state->pos_dir.x_plane = old_xplane * cos(-ROT_SPEED) - state->pos_dir.y_plane * sin(-ROT_SPEED);
		state->pos_dir.y_plane = old_xplane * sin(-ROT_SPEED) + state->pos_dir.y_plane * cos(-ROT_SPEED);
		changed = 1;
	}	
	if (keycode == KEY_RIGHT)
	{
		old_xdir = state->pos_dir.x_dir;
		state->pos_dir.x_dir = old_xdir * cos(ROT_SPEED) - state->pos_dir.y_dir * sin(ROT_SPEED);
		state->pos_dir.y_dir = old_xdir * sin(ROT_SPEED) + state->pos_dir.y_dir * cos(ROT_SPEED);
		old_xplane = state->pos_dir.x_plane;
		state->pos_dir.x_plane = old_xplane * cos(ROT_SPEED) - state->pos_dir.y_plane * sin(ROT_SPEED);
		state->pos_dir.y_plane = old_xplane * sin(ROT_SPEED) + state->pos_dir.y_plane * cos(ROT_SPEED);
		changed = 1;
	}	
	//printf("pos_dir x %f, pos_dir y %f\n", state->pos_dir.x_pos, state->pos_dir.y_pos);
	if (changed == 1)
		state->needs_redraw = 1;
	return (0);
}

int	on_close(t_app_state *state)
{
	destroy_app_state(state);
	exit(0);
	return (0);
}