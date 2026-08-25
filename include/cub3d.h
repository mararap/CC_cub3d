/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/21 17:43:50 by marapovi         ###   ########.fr       */
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
# 	define BUFFER_SIZE 42
# endif

# define WINDOW_WIDTH 1280		// ratio 16:9 -> looks good; Intel UHD 770 (as
# define WINDOW_HEIGHT 720		// integrated in c3r8p8) should be able to handle
# define WINDOW_TITLE "CUB3D"	// that easily; adapt based on CPU performance.

# define PI 3.14159265359
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.1

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

typedef struct s_wall_images
{
	t_image_buffer	north;
	t_image_buffer	south;
	t_image_buffer	east;
	t_image_buffer	west;
}	t_wall_images;

typedef	struct s_pos_dir		// positions and directions
{
	double	x_pos;
	double	y_pos;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
}			t_pos_dir;

typedef struct s_scene			// textures/colors
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		color_floor;
	int		color_ceil;
}			t_scene;

/* typedef struct s_viewport (unused/fractol-remainder?)
{
	long double	x_min;
	long double	x_max;
	long double	y_min;
	long double	y_max;
}	t_viewport; */

typedef struct	s_config_flags
{
	int no_set;
	int so_set;
    int we_set;
    int ea_set;
    int f_set;
    int c_set;
} t_config_flags;

typedef struct s_ray
{
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  side_dist_x;
    double  side_dist_y;
    double  wall_dist;
    int     side;
    int     hit;

}   t_ray;

typedef struct s_draw_column
{
	t_ray			ray;
	t_image_buffer	*texture;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
}	t_draw_column;

typedef struct s_app_state
{
	void			*mlx;
	void			*window;
	t_image_buffer	image;
//	char			set; (unused?)
	t_pos_dir		pos_dir;	
//	t_viewport		viewport;
	t_scene			scene;
//	int				max_iterations; (unused/fractol-remainder?)
	int				needs_redraw;
//	long			last_frame_time_us; (unused?)
	char			**map;
	int				map_height;
	int				map_width;
	t_config_flags	config_flags;
	t_wall_images	wall_images;
}	t_app_state;

char	*get_next_line(int fd);

int		parse_map(int argc, char **argv, t_app_state *state);
int		parser_error(char *message);
int		parser_is_blank(char *line);
void	parser_strip_newline(char *line);
int		parser_is_map_line(char *line);
int		parser_add_map_line(t_app_state *state, char *line);
int		parser_all_config(t_app_state *state);
int		parser_parse_config(t_app_state *state, char *line);
int		parser_set_texture(char *value, char **slot, int *is_set);
int		parser_set_color(char *value, int *slot, int *is_set);
int		parser_validate_map(t_app_state *state);
int		parser_find_player(t_app_state *state);
int		initialize_app(t_app_state *state);
int		on_key_press(int keycode, t_app_state *state);
int		on_close(t_app_state *state);
int		on_loop_tick(t_app_state *state);

void	destroy_app_state(t_app_state *state);

void	put_pixel(t_image_buffer *image, int x, int y, int color);

void	fill_image(t_image_buffer *image, int color);

void	draw_cell(t_app_state *state, int row, int col, int size);

void	render_minimap(t_app_state *state);

void	redraw_frame(t_app_state *state);
void	render_frame(t_app_state *state);

void	set_north_texture(char *line);
void	set_south_texture(char *line);
void	set_west_texture(char *line);
void	set_east_texture(char *line);
void	set_floor_color(char *line);
void	set_ceiling_color(char *line);

void    cast_ray(t_app_state *app, t_ray *ray, int screen_x);


#endif