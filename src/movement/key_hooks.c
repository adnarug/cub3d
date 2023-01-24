/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:40:02 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 17:19:26 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	check_wasd(t_game *game, mlx_key_data_t keycode)
{
	if (keycode.key == MLX_KEY_W
		&& (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		move(game, 0);
	else if (keycode.key == MLX_KEY_S
		&& (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		move(game, M_PI);
	else if (keycode.key == MLX_KEY_A
		&& (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		move(game, 1.5 * M_PI);
	else if (keycode.key == MLX_KEY_D
		&& (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		move(game, 0.5 * M_PI);
}

static void	check_rotate(t_game *game, mlx_key_data_t keycode)
{
	if (keycode.key == MLX_KEY_LEFT && (keycode.action == MLX_PRESS
			|| keycode.action == MLX_REPEAT))
		rotate(game, ROTATE_LEFT);
	else if (keycode.key == MLX_KEY_RIGHT && (keycode.action == MLX_PRESS
			|| keycode.action == MLX_REPEAT))
		rotate(game, ROTATE_RIGHT);
}

static void	check_esc(mlx_key_data_t keycode, t_game *game)
{
	if (keycode.key == MLX_KEY_ESCAPE && keycode.action == MLX_PRESS)
	{
		free_game(game, true);
		system("leaks cub3D");
		exit(EXIT_SUCCESS);
	}
}

void	read_keys(mlx_key_data_t keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	check_wasd(game, keycode);
	check_rotate(game, keycode);
	// check_mouse_keys(game, keycode);
	check_esc(keycode, game);
}
