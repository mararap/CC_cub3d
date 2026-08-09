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

void	put_pixel(t_image_buffer *image, int x, int y, int color)
{
	int		bpp;
	char	*ptr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	bpp = image->bits_per_pixel / 8;
	ptr = image->pixels + y * image->line_stride + x * bpp;
	*(unsigned int *)ptr = (unsigned int)color;
}

static int	get_map_width(t_app_state *state)
{
	int	width;
	int	row;
	int	len;

	width = 0;
	row = 0;
	while (row < state->map_height)
	{
		len = (int)ft_strlen(state->map[row]);
		if (len > width)
			width = len;
		row++;
	}
	return (width);
}

static int	get_cell_size(t_app_state *state, int map_width)
{
	int	cell_w;
	int	cell_h;

	if (map_width == 0 || state->map_height == 0)
		return (1);
	cell_w = WINDOW_WIDTH / map_width;
	cell_h = WINDOW_HEIGHT / state->map_height;
	if (cell_w < 1)
		cell_w = 1;
	if (cell_h < 1)
		cell_h = 1;
	if (cell_w < cell_h)
		return (cell_w);
	return (cell_h);
}

static int	get_color(char c)
{
	if (c == '1')
		return (0x003C3C3C);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x00D8D2C4);
	//if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	//	return (0x00E63946);
	return (0x00111111);
}

static char	get_map_cell(t_app_state *state, int row, int col)
{
	if (row >= state->map_height)
		return (' ');
	if (col >= (int)ft_strlen(state->map[row]))
		return (' ');
	return (state->map[row][col]);
}

static void	fill_image(t_image_buffer *image, int color)
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

static void	draw_cell(t_app_state *state, int row, int col, int size)
{
	int	x;
	int	y;
	int	color;

	color = get_color(get_map_cell(state, row, col));
	y = row * size;
	while (y < (row + 1) * size)
	{
		x = col * size;
		while (x < (col + 1) * size)
		{
			if (y == row * size || y == ((row + 1) * size) - 1 ||
				x == col * size || x == ((col + 1) * size) - 1)
			{
				put_pixel(&state->image, x, y, 0x00333333);
			}
			else
			{
				put_pixel(&state->image, x, y, color);
			}
			x++;
		}
		y++;
	}
}

static void	draw_player(t_app_state *state, int size)
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

void	render_frame(t_app_state *state)
{
	t_ray	ray;
	int		row;
	int		col;
	int		width;
	int		size;

	fill_image(&state->image, 0x00111111);
	width = get_map_width(state);
	size = get_cell_size(state, width);
	row = 0;
	while (row < state->map_height)
	{
		col = 0;
		while (col < width)
		{
			draw_cell(state, row, col, size);
			col++;
		}
		row++;
	}
	draw_player(state, size);
	cast_ray(state, &ray, WINDOW_WIDTH / 2);
	draw_ray_2d(state, &ray, size);
}
