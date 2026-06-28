/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:00:12 by jatanaso          #+#    #+#             */
/*   Updated: 2026/06/28 13:00:27 by jatanaso         ###   ########.fr       */
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
		return (0);
	if (keycode == KEY_A)
		return (0);
	if (keycode == KEY_S)
		return (0);
	if (keycode == KEY_D)
		return (0);
	if (keycode == KEY_LEFT)
		return (0);
	if (keycode == KEY_RIGHT)
		return (0);
	return (0);
}

int	on_close(t_app_state *state)
{
	destroy_app_state(state);
	exit(0);
	return (0);
}