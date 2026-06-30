/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/06/30 13:43:01 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Juliyan

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include "mlx.h"
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WINDOW_WIDTH 400
# define WINDOW_HEIGHT 400
# define WINDOW_TITLE "CUB3D"

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

typedef struct s_image_buffer
{
	void	*handle;
	char	*pixels;
	int		bits_per_pixel;
	int		line_stride;
	int		endian;
	int		width;
	int		height;
}	t_image_buffer;

typedef	struct s_player
{
	double	x_position;
	double	y_position;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
};

typedef struct s_viewport
{
	long double	x_min;
	long double	x_max;
	long double	y_min;
	long double	y_max;
}	t_viewport;

typedef struct s_app_state
{
	void			*mlx;
	void			*window;
	t_image_buffer	image;
	char			set;
	t_viewport		viewport;
	int				max_iterations;
	int				needs_redraw;
	long			last_frame_time_us;
	char			**map;
	int				map_height;
}	t_app_state;

char	*get_next_line(int fd);

int		parse_map(int argc, char **argv, t_app_state *state);
int		initialize_app(t_app_state *state);
int		on_key_press(int keycode, t_app_state *state);
int		on_close(t_app_state *state);
int		on_loop_tick(t_app_state *state);

void	destroy_app_state(t_app_state *state);
void	redraw_frame(t_app_state *state);
void	render_frame(t_app_state *state);
void	put_pixel(t_image_buffer *image, int x, int y, int color);

void	set_north_texture(char *line);
void	set_south_texture(char *line);
void	set_west_texture(char *line);
void	set_east_texture(char *line);
void	set_floor_color(char *line);
void	set_ceiling_color(char *line);

#endif