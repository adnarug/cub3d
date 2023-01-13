/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:42:44 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/13 17:30:32 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	check_collisions(t_game	*data, double new_v[2])
{
	int	old_xmap;
	int	old_ymap;

	old_xmap = data->player->x_pos;
	old_ymap = data->player->y_pos;
	if (data->map->map_filled[(int)new_v[X]][(int)new_v[Y]] == '1')
		return (true);
	if (data->map->map_filled[(int)new_v[X]][old_ymap] == '1'
		&& data->map->map_filled[old_xmap][(int)new_v[Y]] == '1')
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
	// game->player->x_pos += angle;
	game->player->x_pos = new_v_world[X];
	game->player->y_pos = new_v_world[Y];
	// render(game);
	update_minimap(game);
}


void	rotate(t_game *data, int direction)
{
	double	new_angle;

	new_angle = data->player->angle + direction * ROTATION_RADIANS;
	if (new_angle < 0)
		data->player->angle = 2 * M_PI + new_angle;
	else if (new_angle >= 2 * M_PI)
		data->player->angle = new_angle - 2 * M_PI;
	else
		data->player->angle = new_angle;
	data->player->x_scalar = sin(data->player->angle);
	data->player->y_scalar = -1 * cos(data->player->angle);
	data->player->camplane[X] = data->player->x_scalar;
	data->player->camplane[Y] = data->player->y_scalar;
	rotate_vector(data->player->camplane, 0.5 * M_PI);
	update_minimap(data);

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