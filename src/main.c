/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:01:15 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/06 14:50:16 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


//TODO: mapinit to fix the extra step
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

int		init_game(t_game *game)
{
	game->tex = malloc(sizeof(t_textures));
	if (game->tex == NULL)
		return (EXIT_FAILURE);
	game->map = malloc(sizeof(t_map));
	if (game->map == NULL)
		return (EXIT_FAILURE);
	game->tex->no = NULL;
	game->tex->so = NULL;
	game->tex->ea = NULL;
	game->tex->we = NULL;
	game->tex->f = malloc(sizeof(t_tex_rgb));
	if (game->tex->f == NULL)
		return (EXIT_FAILURE);
	game->tex->c = malloc(sizeof(t_tex_rgb));
	if (game->tex->c == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void free_2d(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

int		free_game(t_game *game)
{
	
	free_2d(game->tex->f->rgb);
	free_2d(game->tex->c->rgb);
	free(game->tex->f);
	free(game->tex->c);
	free(game->tex->no);
	free(game->tex->so);
	free(game->tex->we);
	free(game->tex->ea);
	free(game->tex);
	free_2d(game->map->map_raw);
	free_2d(game->map->map_filled);
	// nJWfree(game->map->path);
	free(game->map);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game);
	if (args_check(&game, argc, argv) == EXIT_FAILURE)
		exit(1);
	init_map(&game);
	// launch(&game, argv);
	// mlx_hook(game.window, 2, 0, input, &game);
	// mlx_loop_hook(game.mlx, update, &game);
	// mlx_loop(game.mlx);
	free_game(&game);
	system("leaks cub3D");
	return (0);
}
