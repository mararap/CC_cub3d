/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 00:00:00 by jatanaso          #+#    #+#             */
/*   Updated: 2026/08/29 00:00:00 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# include "cub3d.h"

# define MINIMAP_X 16
# define MINIMAP_Y 16
# define MINIMAP_RAY_STEP 16
# define MINIMAP_MAX_WIDTH 320
# define MINIMAP_MAX_HEIGHT 240

int		minimap_cell_size(t_app_state *state);
void	draw_minimap_cell(t_app_state *state, int row, int column, int size);

#endif
