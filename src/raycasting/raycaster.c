/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:16:23 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/18 16:14:55 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	cast_ray(t_game *game, double dir_x, double dir_y, int win_x)
{
	double	pos[2];
	double	ray[2];
	int		step[2];
	double	deltaDist[2];
	double	map_pos[2];
	double	sideDist[2];
	double	wallDist;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	pos[X] = game->player->x_pos;
	pos[Y] = game->player->y_pos;
	deltaDist[X] = fabs(1 / dir_x);
	deltaDist[Y] = fabs(1 / dir_y);
	map_pos[X] = (int)pos[X];
	map_pos[Y] = (int)pos[Y];
	ray[X] = (double)map_pos[X];
	ray[Y] = (double)map_pos[Y];
	if (dir_x < 0)
	{
		step[X] = -1;
		sideDist[X] = (pos[X] - map_pos[X]) * deltaDist[X];
	}
	else
    {
		step[X] = 1;
		sideDist[X] = (map_pos[X] + 1.0 - pos[X]) * deltaDist[X];
    }
	if (dir_y < 0)
	{
		step[Y] = -1;
		sideDist[Y] = (pos[Y] - map_pos[Y]) * deltaDist[Y];
	}
	else
    {
		step[Y] = 1;
		sideDist[Y] = (map_pos[Y] + 1.0 - pos[Y]) * deltaDist[Y];
    }
	while (1)
	{
		if (sideDist[X]< sideDist[Y])
        {
        	sideDist[X] += deltaDist[X];
        	ray[X] += step[X];
			side = 0;
        }
		else
        {
        	sideDist[Y] += deltaDist[Y];
        	ray[Y] += step[Y];
			side = 1;
		}
		if (game->map->map_filled[(int)ray[X]][(int)ray[Y]] == '1')
 				break ;
	}
	if (side == 0)
		wallDist = sideDist[X] - deltaDist[X];
	else
		wallDist = sideDist[Y] - deltaDist[Y];

	lineHeight = (int)(HEIGHT / wallDist);

    drawStart = (-lineHeight / 2) + (HEIGHT / 2);
    if (drawStart < 0)
		drawStart = 0;
    drawEnd = (lineHeight / 2) + (HEIGHT / 2);
    if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	while (drawStart < drawEnd)
	{
		if (side == 0)
			mlx_put_pixel(game->img, win_x, drawStart, RED);
		else
			mlx_put_pixel(game->img, win_x, drawStart, 0x6E2020FF);
		drawStart++;
	}
}

void	fill_ceiling(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->img, x, y, 0x438B8CFF);
			y++;
		}
		y = 0;
		x++;
	}
}

void	fill_floor(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = HEIGHT / 2;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->img, x, y, 0x433C5CFF);
			y++;
		}
		y = HEIGHT / 2;
		x++;
	}
}

void	raycaster(t_game *game)
{
	double	i;
	double	dir_x;
	double	dir_y;
	double	ray_angle;
	int		win_x;

	i = -0.5;
	win_x = 0;
	fill_ceiling(game);
	fill_floor(game);
	while (win_x < WIDTH)
	{
		ray_angle = game->player->angle;
		ray_angle += i;
		dir_x = sin(ray_angle);
		dir_y = -1 * cos(ray_angle);
		cast_ray(game, dir_x, dir_y, win_x);
		win_x++;
		i += 0.001;
	}
}
