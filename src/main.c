/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:31:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/21 17:27:28 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_loop_tick(t_app_state *state)
{
	if (state->needs_redraw)
		redraw_frame(state);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app_state	state;

	ft_bzero(&state, sizeof(t_app_state));
	if (!parse_map(argc, argv, &state))
		return (destroy_app_state(&state), 1);
	if (!initialize_app(&state))
		return (destroy_app_state(&state), 1);
	mlx_hook(state.window, 2, 1L << 0, &on_key_press, &state);
	mlx_hook(state.window, 17, 0, &on_close, &state);
	mlx_loop_hook(state.mlx, &on_loop_tick, &state);
	redraw_frame(&state);
	mlx_loop(state.mlx);
	destroy_app_state(&state);
	return (0);
}
