/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 16:33:42 by marapovi          #+#    #+#             */
/*   Updated: 2026/09/15 13:37:19 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// lines — ray direction and delta distances:
// 1) map screen_x to Normalized Device Coordinates (NDC) aka
//    a value between -1 and 1 = camera_x
// 2) calculate ray direction using basic vector addition with camera_x as a
//    multiplier that shrinks/streches the plane vector, and flips it if < 0
// 3) truncate the position of the player to (int), to get the map tile the
//    player is standing on
// 4) calculate delta_dist values to get the total linear distance the ray must
//    travel to move exactly 1.0 unit in x/y direction (crossing 1 line) while
// 5) protecting against division by zero
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
// ray->hit         ... flag that changes from 0 to 1 if wall get's hit
// ray->side_dist_x ... distance to the next vertical grid line (x changed)
// ray->side_dist_y ... distande to the next horizontal grid line (y changed)
// side             ... flag to tell if vertical line was crossed (x changed,
//                      side = 0) or if horizontal line was crossed
//                      (y changed, side = 1)

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
			&& ray->map_x < (int)ft_strlen(app->map[ray->map_y])
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
