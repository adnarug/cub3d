/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:48:31 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 14:35:39 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	set_offset(t_game *game)
{
	game->mini->x_offset = (int)game->player->x_pos - MINIMAP_SCOPE / 2;
	game->mini->y_offset = (int)game->player->y_pos - MINIMAP_SCOPE / 2;
	if (game->mini->x_offset + MINIMAP_SCOPE > game->map->max_len)
		game->mini->x_offset = game->map->max_len - MINIMAP_SCOPE;
	if (game->mini->x_offset < 0)
		game->mini->x_offset = 0;
	if (game->mini->y_offset + MINIMAP_SCOPE > game->map->map_clean_lines)
		game->mini->y_offset = game->map->map_clean_lines - MINIMAP_SCOPE;
	if (game->mini->y_offset < 0)
		game->mini->y_offset = 0;
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
	if (y_on_map >= game->map->map_clean_lines)
		return (false);
	if (game->map->map_filled[(int)y_on_map][(int)x_on_map] == '1')
	{
		return (true);
	}
	return (false);
}

void	draw_line (t_game *game, double x, double y)
{
	int i = 15;

	while (i > 0)
	{
		mlx_put_pixel(game->mini->img, (int)x++, (int)y, RED);
		i--;
	}
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
			{
				mlx_put_pixel(game->mini->img, pos[X], (pos[Y]), BLACK);
			}
			pos[X]++;
		}
		pos[Y]++;
	}
}

static int	cast_ray_world_to_map(double offset, double ray, double step)
{
	double	ray_on_screen;

	ray_on_screen = (ray - offset) * step;
	return ((int)round(ray_on_screen));
}

void	rays_minimap_line(t_game *game, double step)
{
	double	cam[2];
	double	factor;
	double	ray[2];
	int		pixel[2];


	cam[X] = game->player->x_pos;
	cam[Y] = game->player->y_pos;
	factor = 0.01;
	while (factor < 0.5)
	{

			ray[X] = cam[X] + (game->player->x_scalar * factor);
			ray[Y] = cam[Y] + (game->player->y_scalar * factor);
			if (ray[X] >= game->mini->size || ray[Y] >= game->mini->size
				|| ray[X] < 0 || ray[Y] < 0)
				break ;
			if (game->map->map_filled[(int)ray[Y]][(int)ray[X]] == '1')
				break ;
			pixel[X] = cast_ray_world_to_map(game->mini->x_offset, ray[X] , step);
			pixel[Y] = cast_ray_world_to_map(game->mini->y_offset, ray[Y], step);
			if (pixel[X] >= game->mini->size || pixel[Y] >= game->mini->size
				|| pixel[X] < 1 || pixel[Y] < 1)
				break ;
			mlx_put_pixel(game->mini->img, pixel[X], pixel[Y], RED);
			factor += 0.01;
	}
}

/*Support function*/
void	rays_minimap_cone(t_game *game, double step)
{
	double	cam[2];
	double	factor;
	double	ray[2];
	int		pixel[2];
	double	i;
	double	ray_x_scalar;
	double	ray_angle;
	double	ray_y_scalar;
	i = -0.5;

	cam[X] = game->player->x_pos;
	cam[Y] = game->player->y_pos;
	factor = 0.01;
	while (i < 0.5)
	{
		ray_angle = game->player->angle;
		ray_angle += i;
		ray_x_scalar = sin(ray_angle);
		ray_y_scalar = -1 * cos(ray_angle);
		factor = 0.01;
		while (factor < game->mini->size)
		{

				ray[X] = cam[X] + (ray_x_scalar * factor);
				ray[Y] = cam[Y] + (ray_y_scalar * factor);
				// printf("cam _x %f x_scalar %f ray x %f cam x %f \n cam_y %f y_scalar %f ray_yy %f cam_y %f\n", cam[X], game->player->x_scalar, ray[X], cam[X], cam[Y], game->player->y_scalar, ray[Y], cam[Y]);
				if (ray[X] >= game->mini->size || ray[Y] >= game->mini->size
					|| ray[X] < 0 || ray[Y] < 0)
					break ;
				if (game->map->map_filled[(int)ray[Y]][(int)ray[X]] == '1')
					break ;
				pixel[X] = cast_ray_world_to_map(game->mini->x_offset, ray[X] , step);
				pixel[Y] = cast_ray_world_to_map(game->mini->y_offset, ray[Y], step);
				if (pixel[X] >= game->mini->size || pixel[Y] >= game->mini->size
					|| pixel[X] < 1 || pixel[Y] < 1)
					break ;
				mlx_put_pixel(game->mini->img, pixel[X], pixel[Y], RED);
				factor += 0.01;
		}
		i += 0.001;

	}
}

static void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	double	step;
	
	step = (double)game->mini->size / MINIMAP_SCOPE;
	set_offset(game);
	y = 0;
	while (y < game->mini->size)
	{
		x = 0;
		while (x < game->mini->size)
		{
			if (check_wall(game, x, y, step) == true)
				mlx_put_pixel(game->mini->img, x, y, GREEN_WALL);
			else
				mlx_put_pixel(game->mini->img, x, y, BACKG);
			x++;
		}
		y++;
	}
	draw_player(game, step);
	if (VIS_RAYS == 1)
		rays_minimap_cone(game, step);
	else
		rays_minimap_line(game, step);
	raycaster(game);
}

void	update_minimap(t_game *game)
{
	init_camera_plane(game);
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->mini->img, 0, 0);
}
