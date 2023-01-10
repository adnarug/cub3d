/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:48:31 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/10 15:05:04 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


static void	set_offset_x_pos(t_game *game)
{
	if (game->mini->x_offset + MINIMAP_SCOPE > game->map->max_len)
		game->mini->x_offset = game->map->max_len - MINIMAP_SCOPE;
	if (game->mini->x_offset < 0)
		game->mini->x_offset = 0;
}

static void	set_offset_y_pos(t_game *game)
{
	if (game->mini->y_offset + MINIMAP_SCOPE > game->map->map_clean_lines)
		game->mini->y_offset = game->map->map_clean_lines - MINIMAP_SCOPE;
	if (game->mini->y_offset < 0)
		game->mini->y_offset = 0;
}

void	set_offset(t_game *game)
{
	game->mini->x_offset = (int)game->player->x_pos - MINIMAP_SCOPE / 2;
	game->mini->y_offset = (int)game->player->y_pos  - MINIMAP_SCOPE / 2;
	set_offset_x_pos(game);
	set_offset_y_pos(game);
}

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
	if (game->map->map_filled[(int)y_on_map][(int)x_on_map] == '1')
	{
				return (true);
	}
	return (false);
}

void	draw_player(t_game *game, double step)
{
	double	cam[2];
	int		pos[2];
	double	r;
	double	x_sqr;
	double	y_sqr;

	r = (double) game->mini->size / 80;
	cam[X] = (game->player->x_pos - game->mini->x_offset) * step;
	cam[Y] = (game->player->y_pos - game->mini->y_offset) * step;
	pos[Y] = (int)(cam[Y] - r);
	while (pos[Y] < (cam[Y] + r))
	{
		pos[X] = (int)(cam[X] - r);
		while (pos[X] < (cam[X] + r))
		{
			x_sqr = (pos[X] - cam[X]) * (pos[X] - cam[X]);
			y_sqr = (pos[Y] - cam[Y]) * (pos[Y] - cam[Y]);
			if (x_sqr + y_sqr < (r * r))
				mlx_put_pixel(game->mini->img, pos[X], (pos[Y]), GREEN);
			pos[X]++;
		}
		pos[Y]++;
	}
}

static void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	double	step;

	// game->mini->size = WIDTH / MINIMAP_FACTOR;
	step = (double)game->mini->size / MINIMAP_SCOPE;
	set_offset(game);
	y = 0;
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
	draw_player(game, step);
	// cast_rays(data, step);
}

void	update_minimap(t_game *game)
{
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->mini->img, 0, 0);
}
