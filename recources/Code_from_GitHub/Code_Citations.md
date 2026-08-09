# Code Citations

## License: unknown
https://github.com/lverdoes/cub3D/blob/9348799f9e504349ccc4377b3903e0da49a4e08f/mandatory/engine/calc_ray_dir.c

```
Here is the DDA algorithm from javidx9 translated to C, wired to your existing structs. This goes into your empty `raycast.c`:

```c
#include "cub3d.h"

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;   // accumulated distance to next x grid line
    double  side_dist_y;   // accumulated distance to next y grid line
    double  delta_dist_x;  // distance between consecutive x grid lines
    double  delta_dist_y;  // distance between consecutive y grid lines
    double  wall_dist;
    int     side;          // 0 = E/W wall hit, 1 = N/S wall hit
}   t_ray;

static void init_ray(t_ray *r, t_pos_dir *pd, int col)
{
    double camera_x;

    // maps screen column to [-1, +1]: left edge = -1, center = 0, right = +1
    camera_x = 2.0 * col / (double)WINDOW_WIDTH - 1.0;
    r->dir_x = pd->x_dir + pd->x_plane * camera_x;
    r->dir_y = pd->y_dir + pd->y_plane * camera_x;
    r->map_x = (int)pd->x_pos;
    r->map_y = (int)pd->y_pos;
    // optimised form: abs(1/dir) instead of sqrt(1 + (dy/dx)^2)
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (pd->x_pos - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - pd->x_pos) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (pd->y_pos - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - pd->y_pos) * r->delta_dist_y;
    }
}

static void dda_walk(t_ray *r, t_app_state *state)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r
```


## License: unknown
https://github.com/DeRuina/cub3D-Advanced-Raycasting/blob/38115c9555ecc54c6362559ae333ebac3b2d9b36/src/ray.c

```
Here is the DDA algorithm from javidx9 translated to C, wired to your existing structs. This goes into your empty `raycast.c`:

```c
#include "cub3d.h"

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;   // accumulated distance to next x grid line
    double  side_dist_y;   // accumulated distance to next y grid line
    double  delta_dist_x;  // distance between consecutive x grid lines
    double  delta_dist_y;  // distance between consecutive y grid lines
    double  wall_dist;
    int     side;          // 0 = E/W wall hit, 1 = N/S wall hit
}   t_ray;

static void init_ray(t_ray *r, t_pos_dir *pd, int col)
{
    double camera_x;

    // maps screen column to [-1, +1]: left edge = -1, center = 0, right = +1
    camera_x = 2.0 * col / (double)WINDOW_WIDTH - 1.0;
    r->dir_x = pd->x_dir + pd->x_plane * camera_x;
    r->dir_y = pd->y_dir + pd->y_plane * camera_x;
    r->map_x = (int)pd->x_pos;
    r->map_y = (int)pd->y_pos;
    // optimised form: abs(1/dir) instead of sqrt(1 + (dy/dx)^2)
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (pd->x_pos - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - pd->x_pos) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (pd->y_pos - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - pd->y_pos) * r->delta_dist_y;
    }
}

static void dda_walk(t_ray *r, t_app_state *state)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r
```


## License: unknown
https://github.com/lverdoes/cub3D/blob/9348799f9e504349ccc4377b3903e0da49a4e08f/mandatory/engine/calc_ray_dir.c

```
Here is the DDA algorithm from javidx9 translated to C, wired to your existing structs. This goes into your empty `raycast.c`:

```c
#include "cub3d.h"

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;   // accumulated distance to next x grid line
    double  side_dist_y;   // accumulated distance to next y grid line
    double  delta_dist_x;  // distance between consecutive x grid lines
    double  delta_dist_y;  // distance between consecutive y grid lines
    double  wall_dist;
    int     side;          // 0 = E/W wall hit, 1 = N/S wall hit
}   t_ray;

static void init_ray(t_ray *r, t_pos_dir *pd, int col)
{
    double camera_x;

    // maps screen column to [-1, +1]: left edge = -1, center = 0, right = +1
    camera_x = 2.0 * col / (double)WINDOW_WIDTH - 1.0;
    r->dir_x = pd->x_dir + pd->x_plane * camera_x;
    r->dir_y = pd->y_dir + pd->y_plane * camera_x;
    r->map_x = (int)pd->x_pos;
    r->map_y = (int)pd->y_pos;
    // optimised form: abs(1/dir) instead of sqrt(1 + (dy/dx)^2)
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (pd->x_pos - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - pd->x_pos) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (pd->y_pos - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - pd->y_pos) * r->delta_dist_y;
    }
}

static void dda_walk(t_ray *r, t_app_state *state)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;
```


## License: unknown
https://github.com/DeRuina/cub3D-Advanced-Raycasting/blob/38115c9555ecc54c6362559ae333ebac3b2d9b36/src/ray.c

```
Here is the DDA algorithm from javidx9 translated to C, wired to your existing structs. This goes into your empty `raycast.c`:

```c
#include "cub3d.h"

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;   // accumulated distance to next x grid line
    double  side_dist_y;   // accumulated distance to next y grid line
    double  delta_dist_x;  // distance between consecutive x grid lines
    double  delta_dist_y;  // distance between consecutive y grid lines
    double  wall_dist;
    int     side;          // 0 = E/W wall hit, 1 = N/S wall hit
}   t_ray;

static void init_ray(t_ray *r, t_pos_dir *pd, int col)
{
    double camera_x;

    // maps screen column to [-1, +1]: left edge = -1, center = 0, right = +1
    camera_x = 2.0 * col / (double)WINDOW_WIDTH - 1.0;
    r->dir_x = pd->x_dir + pd->x_plane * camera_x;
    r->dir_y = pd->y_dir + pd->y_plane * camera_x;
    r->map_x = (int)pd->x_pos;
    r->map_y = (int)pd->y_pos;
    // optimised form: abs(1/dir) instead of sqrt(1 + (dy/dx)^2)
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (pd->x_pos - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - pd->x_pos) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (pd->y_pos - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - pd->y_pos) * r->delta_dist_y;
    }
}

static void dda_walk(t_ray *r, t_app_state *state)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;
```


## License: unknown
https://github.com/lverdoes/cub3D/blob/9348799f9e504349ccc4377b3903e0da49a4e08f/mandatory/engine/calc_ray_dir.c

```
Here is the DDA algorithm from javidx9 translated to C, wired to your existing structs. This goes into your empty `raycast.c`:

```c
#include "cub3d.h"

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;   // accumulated distance to next x grid line
    double  side_dist_y;   // accumulated distance to next y grid line
    double  delta_dist_x;  // distance between consecutive x grid lines
    double  delta_dist_y;  // distance between consecutive y grid lines
    double  wall_dist;
    int     side;          // 0 = E/W wall hit, 1 = N/S wall hit
}   t_ray;

static void init_ray(t_ray *r, t_pos_dir *pd, int col)
{
    double camera_x;

    // maps screen column to [-1, +1]: left edge = -1, center = 0, right = +1
    camera_x = 2.0 * col / (double)WINDOW_WIDTH - 1.0;
    r->dir_x = pd->x_dir + pd->x_plane * camera_x;
    r->dir_y = pd->y_dir + pd->y_plane * camera_x;
    r->map_x = (int)pd->x_pos;
    r->map_y = (int)pd->y_pos;
    // optimised form: abs(1/dir) instead of sqrt(1 + (dy/dx)^2)
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (pd->x_pos - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - pd->x_pos) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (pd->y_pos - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - pd->y_pos) * r->delta_dist_y;
    }
}

static void dda_walk(t_ray *r, t_app_state *state)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y;
            r->side = 1;
        }
        if (r->map_
```


## License: unknown
https://github.com/DeRuina/cub3D-Advanced-Raycasting/blob/38115c9555ecc54c6362559ae333ebac3b2d9b36/src/ray.c

```
Here is the DDA algorithm from javidx9 translated to C, wired to your existing structs. This goes into your empty `raycast.c`:

```c
#include "cub3d.h"

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;   // accumulated distance to next x grid line
    double  side_dist_y;   // accumulated distance to next y grid line
    double  delta_dist_x;  // distance between consecutive x grid lines
    double  delta_dist_y;  // distance between consecutive y grid lines
    double  wall_dist;
    int     side;          // 0 = E/W wall hit, 1 = N/S wall hit
}   t_ray;

static void init_ray(t_ray *r, t_pos_dir *pd, int col)
{
    double camera_x;

    // maps screen column to [-1, +1]: left edge = -1, center = 0, right = +1
    camera_x = 2.0 * col / (double)WINDOW_WIDTH - 1.0;
    r->dir_x = pd->x_dir + pd->x_plane * camera_x;
    r->dir_y = pd->y_dir + pd->y_plane * camera_x;
    r->map_x = (int)pd->x_pos;
    r->map_y = (int)pd->y_pos;
    // optimised form: abs(1/dir) instead of sqrt(1 + (dy/dx)^2)
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (pd->x_pos - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - pd->x_pos) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (pd->y_pos - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - pd->y_pos) * r->delta_dist_y;
    }
}

static void dda_walk(t_ray *r, t_app_state *state)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y;
            r->side = 1;
        }
        if (r->map_
```

