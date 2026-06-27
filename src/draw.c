#include "cub3d.h"

double	smooth_iter(int iter, double mag, int max)
{
	double	log_zn;
	double	nu;

	if (iter == max)
		return ((double)iter);
	if (mag <= 1.0)
		mag = 1.0000001;
	log_zn = log(mag * mag) / 2.0;
	nu = log(log_zn / log(2.0)) / log(2.0);
	return (iter + 1.0 - nu);
}

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

static void	draw_pixel(t_app_state *state, int x, int y)
{
	double	coord_x;
	double	coord_y;
	int		iter;
	double	smooth;
	int		color;

	coord_x = state->viewport.x_min
		+ (state->viewport.x_max - state->viewport.x_min)
		* (double)x / (state->image.width - 1);
	coord_y = state->viewport.y_min
		+ (state->viewport.y_max - state->viewport.y_min)
		* (double)y / (state->image.height - 1);
	if (state->set == 'm')
		iter = mandelbrot_iter(coord_x, coord_y, state, &smooth);
	else
		iter = julia_iter(coord_x, coord_y, state, &smooth);
	smooth = smooth_iter(iter, smooth, state->max_iterations);
	if (smooth >= (double)state->max_iterations)
		color = 0x000000;
	else
		color = get_smooth_color(state, smooth);
	put_pixel(&state->image, x, y, color);
}

static void	draw_row(t_app_state *state, int y)
{
	int	x;

	x = 0;
	while (x < state->image.width)
	{
		draw_pixel(state, x, y);
		x++;
	}
}

void	render_frame(t_app_state *state)
{
	int	y;

	y = 0;
	while (y < state->image.height)
	{
		draw_row(state, y);
		y++;
	}
}