/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 13:16:54 by marapovi          #+#    #+#             */
/*   Updated: 2026/09/19 16:40:34 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Selecting wall texture file:
// Selects the right texture file depending on ray.side and ray_dir_x or
// ray_dir_y and stores its address in column-> texture:
// If ray.side == 0, the ray stopped at a vertical line, so the wall is facing
// either east (ray_dir_x > 0) or west (ray_dir_x < 0).
// If ray.side == 1, the ray stopped at a horizontal line, so the wall is
// facing either north (ray_dir_y > 0) or south (ray_dir_y < 0)
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

// Calculate texture_x:
// Depending on the players position, it's distance to the wall we hit and the
// ray direction, it calculates the value of wall_x, that is then used to
// determine which pixel column of the texture will be used for the current
// wall slice.
// Modulo is used for bounds protection: if tex_x happens to be 64, modulo will
// wrap it to 0, to stay in the valid range. Same for tex_x = 65 -> 1.
// If the ray is pointing towards north or east, the function will flip tex_x
// in order to correct mirroring that otherwise would occur.
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
	column->tex_x = ((int)(wall_x * column->texture->width)
			% column->texture->width);
	if (column->ray.side == 0 && column->ray.ray_dir_x < 0)
		column->tex_x = column->texture->width - column->tex_x - 1;
	if (column->ray.side == 1 && column->ray.ray_dir_y > 0)
		column->tex_x = column->texture->width - column->tex_x - 1;
}
// Calculates what to paint:
// line_height ... visible wall height on the screen
// draw_start ... top pixel of the wall
// draw_end ... bottom pixel of the wall
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

// Draws the pixels for one vertical pixel column to the screen:
// From top to bottom, first paints the ceiling color until y reaches
// draw_start, then paints the texture of the wall until draw_end, then finally
// paints the floor color.
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

// Renders one frame:
// From left window edge (screen_x = 0) to right window edge
// (screen_x = WINDOW_WIDTH), renders the current frame, one pixel row at a
// time.
// In case of bonus, render_overlay will create the minimap.
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
