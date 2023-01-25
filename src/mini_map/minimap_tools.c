/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:39:43 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 13:45:05 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	offset_adjust(double offset, double ray, double step)
{
	double	ray_to_draw;

	ray_to_draw = (ray - offset) * step;
	return ((int)round(ray_to_draw));
}

void	rays_minimap_line(t_game *game, double step)
{
	double	cam[2];
	double	line_len;
	double	ray[2];
	int		pixel[2];

	cam[X] = game->player->x_pos;
	cam[Y] = game->player->y_pos;
	line_len = 0.01;
	while (line_len < 0.2)
	{
		ray[X] = cam[X] + (game->player->x_scalar * line_len);
		ray[Y] = cam[Y] + (game->player->y_scalar * line_len);
		if (ray[X] >= game->mini->size || ray[Y] >= game->mini->size
			|| ray[X] < 0 || ray[Y] < 0)
			break ;
		if (game->map->map_filled[(int)ray[Y]][(int)ray[X]] == '1')
			break ;
		pixel[X] = offset_adjust(game->mini->x_offset, ray[X], step);
		pixel[Y] = offset_adjust(game->mini->y_offset, ray[Y], step);
		if (pixel[X] >= game->mini->size || pixel[Y] >= game->mini->size
			|| pixel[X] < 1 || pixel[Y] < 1)
			break ;
		mlx_put_pixel(game->mini->img, pixel[X], pixel[Y], RED);
		line_len += 0.01;
	}
}
