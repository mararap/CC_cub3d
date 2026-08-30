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

static void	calc_texture_x(t_app_state *state, t_draw_column *column)
{
	double	wall_x;

	if (column->ray.side == 0)
		wall_x = state->pos_dir.y_pos
			+ column->ray.wall_dist * column->ray.ray_dir_y;
	else
		wall_x = state->pos_dir.x_pos
			+ column->ray.wall_dist * column->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	column->tex_x = (int)(wall_x * column->texture->width);
	if (column->ray.side == 0 && column->ray.ray_dir_x < 0)
		column->tex_x = column->texture->width - column->tex_x - 1;
	if (column->ray.side == 1 && column->ray.ray_dir_y > 0)
		column->tex_x = column->texture->width - column->tex_x - 1;
}

static void	select_wall_texture(t_app_state *state,
		t_draw_column *column)
{
	if (column->ray.side == 0)
	{
		if (column->ray.ray_dir_x > 0)
			column->texture = &state->wall_images.west;
		else
			column->texture = &state->wall_images.east;
	}
	else
	{
		if (column->ray.ray_dir_y > 0)
			column->texture = &state->wall_images.north;
		else
			column->texture = &state->wall_images.south;
	}
}

static void	calc_wall_slice(t_draw_column *column)
{
	column->line_height = (int)(WINDOW_HEIGHT / column->ray.wall_dist);
	column->draw_start = (WINDOW_HEIGHT - column->line_height) / 2;
	column->draw_end = column->draw_start + column->line_height - 1;
	if (column->draw_start < 0)
		column->draw_start = 0;
	if (column->draw_end >= WINDOW_HEIGHT)
		column->draw_end = WINDOW_HEIGHT - 1;
}

static void	draw_wall_column(t_app_state *state, t_draw_column *column,
		int screen_x)
{
	int	y;

	y = 0;
	while (y < column->draw_start)
	{
		put_pixel(&state->image, screen_x, y, state->scene.color_ceil);
		y++;
	}
	if (y <= column->draw_end)
		draw_textured_wall(state, column, screen_x);
	y = column->draw_end + 1;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(&state->image, screen_x, y, state->scene.color_floor);
		y++;
	}
}

void	render_frame(t_app_state *state)
{
	t_draw_column	column;
	int				screen_x;

	screen_x = 0;
	while (screen_x < WINDOW_WIDTH)
	{
		cast_ray(state, &column.ray, screen_x);
		select_wall_texture(state, &column);
		calc_texture_x(state, &column);
		calc_wall_slice(&column);
		draw_wall_column(state, &column, screen_x);
		screen_x++;
	}
	render_overlay(state);
}
