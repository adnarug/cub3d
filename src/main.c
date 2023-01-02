/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:01:15 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/02 16:38:00 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static void	launch(t_game *game, char **argv)
// {
// 	game->collects = 0;
// 	game->moves = 0;
// 	game->tilemap = map_init(argv, game);
// 	if (game->tilemap == NULL)
// 		error("Map initialization error");
// 	game->og_collects = game->collects;
// 	game->player.idle_frames = 20;
// 	game->enemy_imgs.basic_anim = 17;
// 	game_init(game);
// 	return ;
// }

int	main(int argc, char **argv)
{
	t_game	game;

	if (args_check(&game, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_map(&game);
	// launch(&game, argv);
	// mlx_hook(game.window, 2, 0, input, &game);
	// mlx_loop_hook(game.mlx, update, &game);
	// mlx_loop(game.mlx);
	return (0);
}
