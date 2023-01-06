/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:48:31 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/06 17:24:17 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	check_wall(t_game *game, int x, int y, double step)
{
	double	x_on_map;
	double	y_on_map;

	x_on_map = game->mini->x_offset + (((double) x) / step);
	y_on_map = game->mini->y_offset + (((double) y) / step);
	if ((x_on_map - round(x_on_map) < 0.03 && x_on_map - \
		round(x_on_map) > -0.03))
		return (false);
	if ((y_on_map - round(y_on_map) < 0.03 && y_on_map - \
		round(y_on_map) > -0.03))
		return (false);
	if (x_on_map >= game->map->max_len)
		return (false);
	if (game->map->map_filled[(int)x_on_map][(int)y_on_map] == '1')
		return (true);
	return (false);
}


static void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	double	step;

	// game->mini->size = WIDTH / MINIMAP_FACTOR;
	step = (double)game->mini->size / MINIMAP_SCOPE;
	// set_offset(data);
	y = 0;
	printf("SIZE: %d\n", game->mini->size);
	while (y < game->mini->size)
	{
		x = 0;
		while (x < game->mini->size)
		{
			if (check_wall(game, x, y, step) == true)
				mlx_put_pixel(game->mini->img, x, y, NAVY);
			else
				mlx_put_pixel(game->mini->img, x, y, 0xFFFFFF1A);
			x++;
		}
		y++;
	}
	// draw_player(data, step);
	// cast_rays(data, step);
}

void	update_minimap(t_game *game)
{
	printf("check\n");
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->mini->img, 0, 0);
}
