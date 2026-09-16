/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 16:33:42 by marapovi          #+#    #+#             */
/*   Updated: 2026/09/16 19:31:08 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Ray direction and delta distances:
// 1) Maps screen_x to Normalized Device Coordinates (NDC) aka
//    a value between -1 and 1 = camera_x; the camera plane is basically
//    what we see on the screen, or, thinking about analog photography,
//    the equivalent to the flat sensor behind the lens;
// 2) Calculates ray direction using basic vector addition with camera_x as a
//    multiplier that shrinks/stretches the plane vector, and flips it if < 0
// 3) Truncates the position of the player to (int), to get the map tile the
//    player is standing on, and stores the value in map_x/map_y for further
//    use and manipulation in dda_walk.
// 4) Calculates delta_dist values to get the total linear distance the ray must
//    travel to move exactly 1.0 unit in x/y direction (crossing 1 line) while
// 5) Protecting against division by zero.
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

// Step direction and distance to first grid crossing:
// 1) Depending on the x-value of the ray_dir vector, determines ray->step_x
//    to be -1 (negative x-value => ray points left) or 1 (positive x-value
//    => ray points right).
// 2) Computes the distance between the player and the next vertical line by
//    first deriving the horizontal distance from the player to the next
//    vertical line to get a value between 0 and 1 as a fraction of the total
//    horizontal width.
//    Then multiplies the total linear distance along the ray from one
//    grid-line to the next - delta_dist_x - with that fraction, to get the
//    distance along the ray from player to grid-line (works because we are
//    dealing with Similar Triangles).
// 3) Evaluates the same parameters for ray_dir_y, step_y and side_dist_y.
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

// DDA walk until wall hit:
// 1) Entering the while loop with ray->hit set to 0, checks which side_dist
//    (x or y) is shorter, aka which grid-line the player is closer to.
// 2) If the player is closer to a vertical grid-line, adds one total linear
//    tile-crossing along the ray (delta_dist_x) to the distance from the
//    player to the current grid line (side_dist_x) and increases/decreases
//    map_x according to the value of step_x.
//    ray->side = 0 because no horizontal line was crossed (in computer graphics,
//    0 is commonly used for x-axis-events, 1 for y-axis-events).
// 3) If the player is closer to a horizontal grid-line, adds one total
//    linear tile-crossing along the ray (delta_dist_y) to the distance from
//    the player to the current grid line (side_dist_y) and increases/decreases
//    map_y according to the value of step_y.
// 4) Before it checks if we reached a wall, it makes sure
//    a) Are the coordinates of that tile inside the maze boundaries?
//    b) Does the pointer to that row exist in memory?
//    Only then, it checks the value of the character in that position inside
//    the map and eventually sets ray->hit to 1.
// 5) Finally, once the flag is set to 1, it "steps out of the wall" by
//    subtracting delta_dist_x or delta_dist_y accordingly.  
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

// Calls the three previous functions one after the other.
// Gets called once per screen column by render_frame.
void	cast_ray(t_app_state *app, t_ray *ray, int screen_x)
{
	init_ray(app, ray, screen_x);
	set_ray_steps(app, ray);
	dda_walk(app, ray);
}
