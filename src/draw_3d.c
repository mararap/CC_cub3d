/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 13:16:54 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/21 18:28:56 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_wall_slice(t_draw_column *col)
{
	col->line_height = (int)(WINDOW_HEIGHT / col->ray.wall_dist);
	col->draw_start = (WINDOW_HEIGHT - col->line_height) / 2;
	col->draw_end = col->draw_start + col->line_height;
	if (col->draw_start < 0)
		col->draw_start = 0;
	if (col->draw_end >= WINDOW_HEIGHT)
		col->draw_end = WINDOW_HEIGHT - 1;
}

static void	draw_wall_column(t_app_state *state, t_draw_column *col, int scrn_x)
{
	int	y;

	y = 0;
	while (y < col->draw_start)
	{
		put_pixel(&state->image, scrn_x, y, 0x00222222);
		y++;
	}
	while (y >= col->draw_start && y <= col->draw_end)
	{
		put_pixel(&state->image, scrn_x, y, 0xFF8A8A8A);
		y++;
	}
	while (y > col->draw_end && y < WINDOW_HEIGHT)
	{
		put_pixel(&state->image, scrn_x, y, 0xFF601A1E);
		y++;
	}
}

void	render_frame(t_app_state *state)
{
	t_draw_column	col;
	int				screen_x;

	screen_x = 0;
 	while (screen_x < WINDOW_WIDTH)
	{
		cast_ray(state, &col.ray, screen_x);
		calc_wall_slice(&col);
		draw_wall_column(state, &col, screen_x);
		screen_x++;
	}
}