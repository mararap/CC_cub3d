/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/28 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_X 16
#define MINIMAP_Y 16
#define MINIMAP_RAY_STEP 16

int		minimap_cell_size(t_app_state *state);
void	draw_minimap_cell(t_app_state *state, int row, int col, int size);

static void	draw_player_marker(t_app_state *state, int size)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = MINIMAP_X + (int)(state->pos_dir.x_pos * size);
	py = MINIMAP_Y + (int)(state->pos_dir.y_pos * size);
	y = py - 3;
	while (y <= py + 3)
	{
		x = px - 3;
		while (x <= px + 3)
		{
			put_pixel(&state->image, x, y, 0x0000FF00);
			x++;
		}
		y++;
	}
}

static void	draw_player_direction(t_app_state *state, int size)
{
	int	px;
	int	py;
	int	i;

	px = MINIMAP_X + (int)(state->pos_dir.x_pos * size);
	py = MINIMAP_Y + (int)(state->pos_dir.y_pos * size);
	i = 0;
	while (i <= size * 2)
	{
		put_pixel(&state->image,
			px + (int)(state->pos_dir.x_dir * i),
			py + (int)(state->pos_dir.y_dir * i), 0x0000FF00);
		i++;
	}
}

static void	draw_ray(t_app_state *state, t_ray *ray, int size)
{
	int	px;
	int	py;
	int	i;

	px = MINIMAP_X + (int)(state->pos_dir.x_pos * size);
	py = MINIMAP_Y + (int)(state->pos_dir.y_pos * size);
	i = 0;
	while (i <= (int)(ray->wall_dist * size))
	{
		put_pixel(&state->image,
			px + (int)(ray->ray_dir_x * i),
			py + (int)(ray->ray_dir_y * i), 0x00FF0000);
		i++;
	}
}

static void	draw_ray_fan(t_app_state *state, int size)
{
	t_ray	ray;
	int		screen_x;

	screen_x = 0;
	while (screen_x < WINDOW_WIDTH)
	{
		cast_ray(state, &ray, screen_x);
		draw_ray(state, &ray, size);
		screen_x += MINIMAP_RAY_STEP;
	}
}

void	render_overlay(t_app_state *state)
{
	int	row;
	int	col;
	int	size;

	size = minimap_cell_size(state);
	row = 0;
	while (row < state->map_height)
	{
		col = 0;
		while (col < state->map_width)
			draw_minimap_cell(state, row, col++, size);
		row++;
	}
	draw_ray_fan(state, size);
	draw_player_marker(state, size);
	draw_player_direction(state, size);
}
