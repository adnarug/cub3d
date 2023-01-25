/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 13:45:47 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	ft_line_count(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	assign_player(t_game *game, int i, int j, int *one_pl_found)
{
	if (ft_strchr(PLAYER_POS, game->map->map_filled[i][j]) != NULL)
	{
		if (*one_pl_found == 1)
			return (EXIT_FAILURE);
		*one_pl_found = 1;
		game->player->x_pos = j + 0.5;
		game->player->y_pos = i + 0.5;
		game->player->dir = game->map->map_filled[i][j];
		game->map->map_filled[i][j] = '0';
		init_player_angle(game);
	}
	return (EXIT_SUCCESS);
}
