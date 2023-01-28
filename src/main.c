/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:01:15 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 12:55:54 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error("Error\nWrong input - check the parameters\n"));
	if (init_game(&game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_mlx(&game);
	if (args_check(&game, argc, argv) == EXIT_FAILURE)
	{
		free_game_prs(&game);
		system("leaks cub3D");
		exit(1);
	}
	init_map(&game);
	launch_minimap(&game);
	mlx_key_hook(game.mlx, &read_keys, (void *)&game);
	mlx_loop(game.mlx);
	free_game(&game, true);
	return (0);
}
