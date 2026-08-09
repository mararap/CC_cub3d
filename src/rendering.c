/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi@student.42vienna.com <marapovi    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:38:20 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/09 19:10:12 by marapovi@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
//Maria

// create frame content (corridors, walls, floor, ceiling...)

/* The use of images of the minilibX library is strongly recommended.*/

/*
Except for the map, each element must begin with its type identifier (composed
by one or two characters), followed by its specific information in a strict order:

- North texture:
NO ./path_to_the_north_texture
· identifier: NO
· path to the north texture

- South texture:
SO ./path_to_the_south_texture
· identifier: SO
· path to the south texture

- West texture:
WE ./path_to_the_west_texture
· identifier: WE
· path to the west texture

- East texture:
EA ./path_to_the_east_texture
· identifier: EA
· path to the east texture

- Floor color:
F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255

- Ceiling color:
C 225,30,0
· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255
*/

void	set_north_texture(char *line)
{
    char    *path;
    int     fd;

    path = ft_strtrim(line + 2, " \t\n");
    if (path == NULL)
        exit(EXIT_FAILURE);

    fd = open(path, O_RDONLY);
    free(path);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(fd);
}
void	set_south_texture(char *line)
{
    char    *path;
    int     fd;

    path = ft_strtrim(line + 2, " \t\n");
    if (path == NULL)
        exit(EXIT_FAILURE);

    fd = open(path, O_RDONLY);
    free(path);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(fd);
}
void	set_west_texture(char *line)
{
    char    *path;
    int     fd;

    path = ft_strtrim(line + 2, " \t\n");
    if (path == NULL)
        exit(EXIT_FAILURE);

    fd = open(path, O_RDONLY);
    free(path);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(fd);
}
void	set_east_texture(char *line)
{
    char    *path;
    int     fd;

    path = ft_strtrim(line + 2, " \t\n");
    if (path == NULL)
        exit(EXIT_FAILURE);

    fd = open(path, O_RDONLY);
    free(path);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(fd);
}
void	set_floor_color(char *line)
{
    (void)line;
    // parse line and set state->scene.color_floor
}
void	set_ceiling_color(char *line)
{
    (void)line;
    // parse line and set state->scene.color_ceiling
}