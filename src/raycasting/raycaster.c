/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:16:23 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/22 14:32:43 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_side_dist(t_raycast *ray, double *map_pos, double *pos)
{
	if (ray->dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (pos[X] - map_pos[X]) * ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = (map_pos[X] + 1.0 - pos[X]) * ray->delta_dist[X];
	}
	if (ray->dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (pos[Y] - map_pos[Y]) * ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = (map_pos[Y] + 1.0 - pos[Y]) * ray->delta_dist[Y];
	}
}

static void	calculate_side_dist(t_game *game, t_raycast *ray)
{
	while (1)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->ray_pos[X] += ray->step[X];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->ray_pos[Y] += ray->step[Y];
			ray->side = 1;
		}
		if (game->map->map_filled \
			[(int)ray->ray_pos[X]][(int)ray->ray_pos[Y]] == '1')
			break ;
	}
}

void	cast_ray(t_game *game, t_raycast *ray, int win_x)
{
	double	pos[2];
	double	map_pos[2];

	pos[X] = game->player->x_pos;
	pos[Y] = game->player->y_pos;
	ray->delta_dist[X] = fabs(1 / ray->dir[X]);
	ray->delta_dist[Y] = fabs(1 / ray->dir[Y]);
	map_pos[X] = (int)pos[X];
	map_pos[Y] = (int)pos[Y];
	ray->ray_pos[X] = (double)map_pos[X];
	ray->ray_pos[Y] = (double)map_pos[Y];
	init_side_dist(ray, map_pos, pos);
	calculate_side_dist(game, ray);
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist[X] - ray->delta_dist[X];
	else
		ray->wall_dist = ray->side_dist[Y] - ray->delta_dist[Y];
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	texturize(game, win_x, ray);
}

void	raycaster(t_game *game)
{
	t_raycast	ray;
	double		camera[2];
	int			win_x;

	win_x = 0;
	extract_hex_color(game);
	fill_ceiling(game);
	fill_floor(game);
	while (win_x < WIDTH)
	{
		camera[X] = 2 * win_x / (double)WIDTH - 1;
		ray.dir[X] = game->player->x_scalar + \
			game->player->camplane[X] * camera[X];
		ray.dir[Y] = game->player->y_scalar + \
			game->player->camplane[Y] * camera[X];
		cast_ray(game, &ray, win_x);
		win_x++;
	}
}
