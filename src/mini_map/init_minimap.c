/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:53:41 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 15:09:30 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*Creating a spaceholder for the minimap*/
void	start_minimap(t_game *game)
{
	game->mini = malloc(sizeof(t_mini));
	if (!game->mini)
	{
		error("Error\nFailed to start minimap\n");
		exit(1);
	}
	game->mini->size = WIDTH / MINIMAP_SCALE;
	game->mini->img = NULL;
	game->mini->img = mlx_new_image(game->mlx, \
		game->mini->size, game->mini->size);
}

void	launch_minimap(t_game *game)
{
	start_minimap(game);
	update_minimap(game);
}
