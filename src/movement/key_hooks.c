/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:40:02 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/11 16:45:20 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	check_WASD(t_game *game, mlx_key_data_t keycode)
{
	if (keycode.key == MLX_KEY_W && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
			move(game, 0);
		// printf("Coordinates - x:%f y:%f\n", game->player->x_pos, game->player->y_pos);
		// if (check_step(game, game->player->x_pos, game->player->y_pos - 0.3) == EXIT_SUCCESS)
		// 	game->player->y_pos -= 0.3;
	}
	else if (keycode.key == MLX_KEY_S && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
			move(game, M_PI);
		// printf("Coordinates - x:%f y:%f\n", game->player->x_pos, game->player->y_pos);
		// if (check_step(game, game->player->x_pos, game->player->y_pos + 0.3) == EXIT_SUCCESS)
		// 	game->player->y_pos += 0.3;
	}
	else if (keycode.key == MLX_KEY_A && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
			move(game, 1.5 * M_PI);
		// printf("Coordinates - x:%f y:%f\n", game->player->x_pos, game->player->y_pos);
		// if (check_step(game, game->player->x_pos - 0.3, game->player->y_pos) == EXIT_SUCCESS)
		// 	game->player->x_pos -= 0.3;
	}
	else if (keycode.key == MLX_KEY_D && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
	{
			move(game, 0.5 * M_PI);
		// printf("Coordinates - x:%f y:%f\n", game->player->x_pos, game->player->y_pos);
		// if (check_step(game, game->player->x_pos + 0.3, game->player->y_pos) == EXIT_SUCCESS)
		// 	game->player->x_pos += 0.3;
	}
	// update_minimap(game);
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

static void	check_esc(t_game *game, mlx_key_data_t keycode)
{
	if (keycode.key == MLX_KEY_ESCAPE && keycode.action == MLX_PRESS)
	{
		// system("leaks cub3D");
		exit(EXIT_SUCCESS);
	}
}

void	read_keys(mlx_key_data_t keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	check_WASD(game, keycode);
	check_rotate(game, keycode);
	// check_mouse_keys(game, keycode);
	check_esc(game, keycode);
}