// handle keys/movement

/*
◦ The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
◦ The W, A, S, and D keys must allow you to move the point of view through
the maze.
◦ Pressing ESC must close the window and quit the program cleanly.
◦ Clicking on the red cross on the window’s frame must close the window and
quit the program cleanly.*/

#include "fractol.h"

static void	handle_pan_keys(int keycode, t_app_state *state,
			double viewport_width, double viewport_height)
{
	double	pan_fraction;

	pan_fraction = 0.1;
	if (keycode == KEY_LEFT)
		pan_viewport(state, -viewport_width * pan_fraction, 0);
	if (keycode == KEY_RIGHT)
		pan_viewport(state, viewport_width * pan_fraction, 0);
	if (keycode == KEY_UP)
		pan_viewport(state, 0, -viewport_height * pan_fraction);
	if (keycode == KEY_DOWN)
		pan_viewport(state, 0, viewport_height * pan_fraction);
}

int	on_key_press(int keycode, t_app_state *state)
{
	double	viewport_width;
	double	viewport_height;

	viewport_width = state->viewport.x_max - state->viewport.x_min;
	viewport_height = state->viewport.y_max - state->viewport.y_min;
	if (keycode == KEY_ESC)
		return (on_close(state));
	if (keycode == KEY_R)
		reset_viewport(state);
	if (keycode == KEY_H)
		state->show_help_overlay = !state->show_help_overlay;
	if (keycode == KEY_P)
	{
		state->palette_index = (state->palette_index + 1) % MAX_PALETTES;
		state->needs_redraw = 1;
	}
	if (keycode == KEY_S)
		save_screenshot_ppm(state);
	handle_pan_keys(keycode, state, viewport_width, viewport_height);
	state->needs_redraw = 1;
	return (0);
}


int	on_close(t_app_state *state)
{
	destroy_app_state(state);
	exit(0);
	return (0);
}