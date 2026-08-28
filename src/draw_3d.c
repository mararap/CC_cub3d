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

static unsigned int	get_texture_pixel(t_image_buffer *texture,
		int x, int y)
{
	char	*pixel;
	int		bytes_per_pixel;

	bytes_per_pixel = texture->bits_per_pixel / 8;
	pixel = texture->pixels + y * texture->line_stride
		+ x * bytes_per_pixel;
	return (*(unsigned int *)pixel);
}

static void	draw_textured_wall(t_app_state *state,
		t_draw_column *col, int screen_x)
{
	double			step;
	double			tex_pos;
	int				tex_y;
	int				y;
	unsigned int	color;

	step = (double)col->texture->height / col->line_height;
	tex_pos = (col->draw_start - WINDOW_HEIGHT / 2.0
			+ col->line_height / 2.0) * step;
	y = col->draw_start;
	while (y <= col->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_texture_pixel(col->texture, col->tex_x, tex_y);
		put_pixel(&state->image, screen_x, y, color);
		y++;
	}
}

static void	calc_texture_x(t_app_state *state, t_draw_column *col)
{
	double	wall_x;

	if (col->ray.side == 0)
		wall_x = state->pos_dir.y_pos
			+ col->ray.wall_dist * col->ray.ray_dir_y;
	else
		wall_x = state->pos_dir.x_pos
			+ col->ray.wall_dist * col->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	col->tex_x = (int)(wall_x * col->texture->width);
	if (col->ray.side == 0 && col->ray.ray_dir_x < 0)
		col->tex_x = col->texture->width - col->tex_x - 1;
	if (col->ray.side == 1 && col->ray.ray_dir_y > 0)
		col->tex_x = col->texture->width - col->tex_x - 1;
}

static void select_wall_texture(t_app_state *state, t_draw_column *col)
{
	if (col->ray.side == 0)
	{
		if (col->ray.ray_dir_x > 0)
			col->texture = &state->wall_images.east;
		else
			col->texture = &state->wall_images.west;
	}
	else
	{
		if (col->ray.ray_dir_y > 0)
			col->texture = &state->wall_images.south;
		else
			col->texture = &state->wall_images.north;
	}
}

static void	calc_wall_slice(t_draw_column *col)
{
	col->line_height = (int)(WINDOW_HEIGHT / col->ray.wall_dist);
	col->draw_start = (WINDOW_HEIGHT - col->line_height) / 2;
	col->draw_end = col->draw_start + col->line_height - 1;
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
		put_pixel(&state->image, scrn_x, y, state->scene.color_ceil);
		y++;
	}
	while (y >= col->draw_start && y <= col->draw_end)
	{
		draw_textured_wall(state, col, scrn_x);
		y = col->draw_end + 1;
	}
	while (y > col->draw_end && y < WINDOW_HEIGHT)
	{
		put_pixel(&state->image, scrn_x, y, state->scene.color_floor);
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
		select_wall_texture(state, &col);
		calc_texture_x(state, &col);
		calc_wall_slice(&col);
		draw_wall_column(state, &col, screen_x);
		screen_x++;
	}
}