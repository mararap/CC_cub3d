/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:52:40 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/20 13:06:33 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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