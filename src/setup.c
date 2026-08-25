/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 12:53:25 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/21 17:26:43 by marapovi         ###   ########.fr       */
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

static int	load_texture(t_app_state *state, t_image_buffer *texture, char *path)
{
	/* Load the XPM handle */
	/* Get its pixel-data address */
	/* Return 1 on success, 0 on failure */
	texture->handle = mlx_xpm_file_to_image(state->mlx, path, 
		&texture->width, &texture->height);
	if (texture->handle == NULL)
	{
		parser_error("Texture loading failed");
		return 0;
	}
	texture->pixels = mlx_get_data_addr(
		texture->handle,
		&texture->bits_per_pixel,
		&texture->line_stride,
		&texture->endian);
	if (texture->pixels == NULL)
		return 0;
	return 1;
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
	if (!load_texture(state, &state->wall_images.north,
		state->scene.tex_no))
		return (0);
	if (!load_texture(state, &state->wall_images.south,
		state->scene.tex_so))
		return (0);
	if (!load_texture(state, &state->wall_images.east,
		state->scene.tex_ea))
		return (0);
	if (!load_texture(state, &state->wall_images.west,
		state->scene.tex_we))
		return (0);
	return (1);
}

void	redraw_frame(t_app_state *state)
{
	render_frame(state);
	mlx_put_image_to_window(state->mlx, state->window,
		state->image.handle, 0, 0);
	state->needs_redraw = 0;
}
