/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:42:44 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 14:57:45 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static bool	check_collisions(t_game	*game, double new_v[2])
{
	int	old_xmap;
	int	old_ymap;

	old_xmap = game->player->x_pos;
	old_ymap = game->player->y_pos;
	if (game->map->map_filled[(int)new_v[Y]][(int)new_v[X]] == '1')
		return (true);
	if (game->map->map_filled[(int)new_v[Y]][old_xmap] == '1'
		&& game->map->map_filled[old_ymap][(int)new_v[X]] == '1')
		return (true);
	return (false);
}

void	move(t_game *game, double angle)
{
	double	new_v[2];
	double	new_v_world[2];

	new_v[X] = STEP * game->player->x_scalar;
	new_v[Y] = STEP * game->player->y_scalar;
	rotate_vector(new_v, angle);
	new_v_world[X] = game->player->x_pos + new_v[X];
	new_v_world[Y] = game->player->y_pos + new_v[Y];
	if (check_collisions(game, new_v_world) == true)
		return ;
	game->player->x_pos = new_v_world[X];
	game->player->y_pos = new_v_world[Y];
	update_minimap(game);
}

void	rotate(t_game *game, int direction)
{
	double	new_angle;

	new_angle = game->player->angle + direction * ROTATION_RADIANS;
	if (new_angle < 0)
		game->player->angle = 2 * M_PI + new_angle;
	else if (new_angle >= 2 * M_PI)
		game->player->angle = new_angle - 2 * M_PI;
	else
		game->player->angle = new_angle;
	game->player->x_scalar = sin(game->player->angle);
	game->player->y_scalar = -1 * cos(game->player->angle);
	game->player->camplane[X] = game->player->x_scalar;
	game->player->camplane[Y] = game->player->y_scalar;
	rotate_vector(game->player->camplane, 0.5 * M_PI);
	update_minimap(game);
}

void	rotate_vector(double v[2], double angle)
{
	double	transf_x;
	double	transf_y;
	double	sin_angle;
	double	cos_angle;
	double	t[2][2];

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	t[0][0] = cos_angle;
	t[0][1] = sin_angle;
	t[1][0] = -1 * sin_angle;
	t[1][1] = cos_angle;
	transf_x = (v[X] * t[I][X]) + (v[Y] * t[J][X]);
	transf_y = (v[X] * t[I][Y]) + (v[Y] * t[J][Y]);
	v[X] = transf_x;
	v[Y] = transf_y;
}
