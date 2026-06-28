/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 12:53:25 by jatanaso          #+#    #+#             */
/*   Updated: 2026/06/28 12:56:05 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Juliyan

// initialize library
// create window

#include "cub3d.h"

static int	init_window(t_app_state *state)
{
	state->mlx = mlx_init();
	if (!state->mlx)
	{
		write(2, "Error: mlx_init failed\n", 24);
		return (0);
	}
	state->window = mlx_new_window(state->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_TITLE);
	if (!state->window)
	{
		write(2, "Error: mlx_new_window failed\n", 30);
		return (0);
	}
	return (1);
}

static int	init_image(t_app_state *state)
{
	state->image.handle = mlx_new_image(state->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!state->image.handle)
	{
		write(2, "Error: mlx_new_image failed\n", 29);
		return (0);
	}
	state->image.pixels = mlx_get_data_addr(state->image.handle,
			&state->image.bits_per_pixel,
			&state->image.line_stride,
			&state->image.endian);
	if (!state->image.pixels)
	{
		write(2, "Error: mlx_get_data_addr failed\n", 33);
		return (0);
	}
	state->image.width = WINDOW_WIDTH;
	state->image.height = WINDOW_HEIGHT;
	return (1);
}
int	initialize_app(t_app_state *state)
{
	if (!init_window(state))
		return (0);
	if (!init_image(state))
		return (0);
	state->needs_redraw = 1;
	return (1);
}

void	redraw_frame(t_app_state *state)
{
	render_frame(state);
	mlx_put_image_to_window(state->mlx, state->window,
		state->image.handle, 0, 0);
	state->needs_redraw = 0;
}
