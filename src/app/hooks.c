/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 00:00:00 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/29 00:00:00 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_loop_tick(t_app_state *state)
{
	if (state->needs_redraw)
		redraw_frame(state);
	return (0);
}

static int	on_close(t_app_state *state)
{
	close_app(state);
	return (0);
}

void	register_hooks(t_app_state *state)
{
	mlx_hook(state->window, 2, 1L << 0, &on_key_press, state);
	mlx_hook(state->window, 17, 0, &on_close, state);
	mlx_loop_hook(state->mlx, &on_loop_tick, state);
}
