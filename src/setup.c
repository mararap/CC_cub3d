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
	state->palette_index = 0;
	state->zoom = 1.0;
	state->max_iterations = 50 + 10 * log2(state->zoom);
	state->show_help_overlay = 0;
	state->needs_redraw = 1;
	initialize_palettes(state);
	reset_viewport(state);
	return (1);
}

void	reset_viewport(t_app_state *state)
{
	state->zoom = 1.0;
	if (state->set == 'm')
	{
		state->viewport.x_min = -2.5;
		state->viewport.x_max = 1.0;
		state->viewport.y_min = -1.5;
		state->viewport.y_max = 1.5;
	}
	else if (state->set == 'j')
	{
		state->viewport.x_min = -2.0;
		state->viewport.x_max = 2.0;
		state->viewport.y_min = -2.0;
		state->viewport.y_max = 2.0;
	}
	else
		write(2, "Error: viewport failed\n", 23);
}

void	redraw_frame(t_app_state *state)
{
	struct timeval	time_val;
	long			start_us;
	long			end_us;

	gettimeofday(&time_val, NULL);
	start_us = time_val.tv_sec * 1000000L + time_val.tv_usec;
	state->needs_redraw = 0;
	render_frame(state);
	mlx_put_image_to_window(state->mlx, state->window,
		state->image.handle, 0, 0);
	if (state->show_help_overlay)
	{
		mlx_string_put(state->mlx, state->window, 8, 14, 0xFFFF00,
			"R reset; H help");
		mlx_string_put(state->mlx, state->window, 8, 28, 0xFFFF00,
			"P palette");
		mlx_string_put(state->mlx, state->window, 8, 42, 0xFFFF00,
			"S shot");
	}
	gettimeofday(&time_val, NULL);
	end_us = time_val.tv_sec * 1000000L + time_val.tv_usec;
	state->last_frame_time_us = end_us - start_us;
}