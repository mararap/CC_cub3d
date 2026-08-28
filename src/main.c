/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:31:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/21 17:27:28 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_scene(t_scene *scene)
{
	free(scene->tex_no);
	free(scene->tex_so);
	free(scene->tex_we);
	free(scene->tex_ea);
	scene->tex_no = NULL;
	scene->tex_so = NULL;
	scene->tex_we = NULL;
	scene->tex_ea = NULL;
}

static void	destroy_image(t_app_state *state, t_image_buffer *image)
{
	if (!state->mlx || !image->handle)
		return ;
	mlx_destroy_image(state->mlx, image->handle);
	image->handle = NULL;
	image->pixels = NULL;
}

void	destroy_app_state(t_app_state *state)
{
	if (!state)
		return ;
	if (state->map)
	{
		free_map(state->map);
		state->map = NULL;
	}
	free_scene(&state->scene);
	destroy_image(state, &state->image);
	destroy_image(state, &state->wall_images.north);
	destroy_image(state, &state->wall_images.south);
	destroy_image(state, &state->wall_images.east);
	destroy_image(state, &state->wall_images.west);
	if (state->mlx && state->window)
	{
		mlx_destroy_window(state->mlx, state->window);
		state->window = NULL;
	}
	if (state->mlx)
	{
		mlx_destroy_display(state->mlx);
		free(state->mlx);
		state->mlx = NULL;
	}
}

int	on_loop_tick(t_app_state *state)
{
	if (state->needs_redraw)
	{
		render_frame(state);
		mlx_put_image_to_window(state->mlx, state->window,
			state->image.handle, 0, 0);
		state->needs_redraw = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_app_state	state;

	ft_bzero(&state, sizeof(t_app_state));
	if (!parse_map(argc, argv, &state))
		return (destroy_app_state(&state), 1);
	if (!initialize_app(&state))
		return (destroy_app_state(&state), 1);
	printf("pos_x %f, pos_y %f", state.pos_dir.x_pos, state.pos_dir.y_pos);
	mlx_hook(state.window, 2, 1L << 0, &on_key_press, &state);
	mlx_hook(state.window, 17, 0, &on_close, &state);
	mlx_loop_hook(state.mlx, &on_loop_tick, &state);
	redraw_frame(&state);
	mlx_loop(state.mlx);
	destroy_app_state(&state);
	return (0);
}
