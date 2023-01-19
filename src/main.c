/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:01:15 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/19 17:06:01 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/*ToDo: 
- fish eye
*/
int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game);
	init_mlx(&game);
	if (args_check(&game, argc, argv) == EXIT_FAILURE)
		exit(1);
	init_map(&game);
	launch_minimap(&game);
	mlx_key_hook(game.mlx, &read_keys, (void *)&game);
	// launch(&game, argv);
	// mlx_hook(game.window, 2, 0, input, &game);
	// mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	// system("leaks cub3D");
	return (0);
}
