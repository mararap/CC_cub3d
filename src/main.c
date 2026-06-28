/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:31:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/06/28 12:48:53 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_app_state(t_app_state *state)
{
	if (!state)
		return ;
	if (state->mlx && state->image.handle)
	{
		mlx_destroy_image(state->mlx, state->image.handle);
		state->image.handle = NULL;
		state->image.pixels = NULL;
	}
	if (state->mlx && state->window)
	{
		mlx_destroy_window(state->mlx, state->window);
		state->window = NULL;
	}
	if (state->mlx)
	{
		mlx_destroy_display(state->mlx);
		free(state->mlx);
		state->mlx = NULL;
	}
}

int	on_loop_tick(t_app_state *state)
{
	if (state->needs_redraw)
	{
		render_frame(state);
		mlx_put_image_to_window(state->mlx, state->window,
			state->image.handle, 0, 0);
		state->needs_redraw = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_app_state	app;

	ft_bzero(&app, sizeof(t_app_state));
	if (!parse_map(argc, argv, &app))
		return (destroy_app_state(&app), 1);
	if (!initialize_app(&app))
		return (destroy_app_state(&app), 1);
	mlx_hook(app.window, 2, 1L << 0, &on_key_press, &app);
	mlx_hook(app.window, 17, 0, &on_close, &app);
	mlx_loop_hook(app.mlx, &on_loop_tick, &app);
	redraw_frame(&app);
	mlx_loop(app.mlx);
	destroy_app_state(&app);
	return (0);
}
