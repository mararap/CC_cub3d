/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 12:34:03 by jatanaso          #+#    #+#             */
/*   Updated: 2026/06/28 12:34:03 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_image(t_image_buffer *image, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_app_state *state, int size)
{
	int	px;
	int	py;
	int	r;
	int	x;
	int	y;
	int	i;

	px = (int)(state->pos_dir.x_pos * size);
	py = (int)(state->pos_dir.y_pos * size);
	r = 6;
	y = py - r;
	while (y <= py + r)
	{
		x = px - r;
		while (x <= px + r)
		{
			put_pixel(&state->image, x, y, 0x0000FF00);
			x++;
		}
		y++;
	}
	i = 0;
	while (i <= 20)
	{
		put_pixel(&state->image,
			px + (int)(state->pos_dir.x_dir * i),
			py + (int)(state->pos_dir.y_dir * i),
			0x0000FF00);
		i++;
	}
}

static void	draw_ray_2d(t_app_state *state, t_ray *ray, int size)
{
    int	px;
    int	py;
    int	i;

    px = (int)(state->pos_dir.x_pos * size);
    py = (int)(state->pos_dir.y_pos * size);
    i = 0;
    while (i <= (int)(ray->wall_dist * size))
    {
        put_pixel(&state->image,
            px + (int)(ray->ray_dir_x * i),
            py + (int)(ray->ray_dir_y * i),
            0x00FF0000);
        i++;
    }
}

void	cast_ray_fan(t_app_state *state, int size)
{
	t_ray	ray;
	int		screen_x;

	screen_x = 0;
	while (screen_x <= WINDOW_WIDTH)
	{
		cast_ray(state, &ray, screen_x);
		draw_ray_2d(state, &ray, size);
		screen_x += 1;
	}
}
