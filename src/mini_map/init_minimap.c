/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:53:41 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/06 17:19:51 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_minimap(t_game *game)
{
	game->mini = NULL;
	game->mini = malloc(sizeof(t_mini));
	if (!game->mini)
	{
		// print_int_error(MALLOC_ERROR, NULL);
		// ft_free_all_and_exit(data);
		error("Error\nFailed to init minimap\n");
		exit(1);
	}
	game->mini->size = WIDTH / MINIMAP_FACTOR;
	game->mini->img = NULL;
}

void	create_minimap(t_game *game)
{
	init_minimap(game);
	game->mini->img = mlx_new_image(game->mlx, \
	game->mini->size, game->mini->size);
}
