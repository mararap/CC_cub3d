/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:31:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/06/21 17:14:36 by marapovi         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_app_state	app;

	if (!parse_map(ac, av, &app))
	{
		print_usage();
		return (1);
	}
	if (!initialize_app(&app))
	{
		destroy_app_state(&app);
		return (1);
	}
	mlx_hook(app.window, 2, 1L << 0, &on_key_press, &app);
	mlx_hook(app.window, 17, 0, &on_close, &app);
	mlx_loop_hook(app.mlx, &on_loop_tick, &app);
	redraw_frame(&app);
	mlx_loop(app.mlx);
	destroy_app_state(&app);
	return (0);
}