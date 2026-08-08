/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:00:12 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/08 17:56:21 by marapovi         ###   ########.fr       */
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
	if (keycode == KEY_ESC)
		return (on_close(state));
	if (keycode == KEY_W)
		state->pos_dir.y_pos -= 0.1;
	if (keycode == KEY_A)
		state->pos_dir.x_pos -= 0.1;
	if (keycode == KEY_S)
		state->pos_dir.y_pos += 0.1;
	if (keycode == KEY_D)
		state->pos_dir.x_pos += 0.1;
	if (keycode == KEY_LEFT)
		return (0);
	if (keycode == KEY_RIGHT)
		return (0);
	//printf("pos_dir x %f, pos_dir y %f\n", state->pos_dir.x_pos, state->pos_dir.y_pos);
	state->needs_redraw = 1;
	return (0);
}

int	on_close(t_app_state *state)
{
	destroy_app_state(state);
	exit(0);
	return (0);
}