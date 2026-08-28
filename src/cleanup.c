/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/28 00:00:00 by jatanaso         ###   ########.fr       */
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
