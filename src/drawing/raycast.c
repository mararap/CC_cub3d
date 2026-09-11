/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 16:33:42 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/14 16:38:50 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// lines — ray direction and delta distances
static void	init_ray(t_app_state *app, t_ray *ray, int screen_x)
{
	double	camera_x;

	camera_x = 2.0 * screen_x / (double)WINDOW_WIDTH - 1.0;
	ray->ray_dir_x = app->pos_dir.x_dir + app->pos_dir.x_plane * camera_x;
	ray->ray_dir_y = app->pos_dir.y_dir + app->pos_dir.y_plane * camera_x;
	ray->map_x = (int)app->pos_dir.x_pos;
	ray->map_y = (int)app->pos_dir.y_pos;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

// step direction and distance to first grid crossing
static void	set_ray_steps(t_app_state *app, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (app->pos_dir.x_pos - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - app->pos_dir.x_pos)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (app->pos_dir.y_pos - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - app->pos_dir.y_pos)
			* ray->delta_dist_y;
	}
}

// DDA walk until wall hit
static void	dda_walk(t_app_state *app, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < app->map_height && ray->map_x >= 0
			&& app->map[ray->map_y] && app->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

// public — called once per screen column from render_frame
void	cast_ray(t_app_state *app, t_ray *ray, int screen_x)
{
	init_ray(app, ray, screen_x);
	set_ray_steps(app, ray);
	dda_walk(app, ray);
}
