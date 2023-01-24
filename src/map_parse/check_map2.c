/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:47:13 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 16:58:34 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	check_diag_holes(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	i = 1;
	j = 1;
	map = game->map->map_filled;
	while (map[i + 1] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' && ((map[i - 1][j + 1] == '-') || \
			(map[i + 1][j - 1] == '-') || \
			(map[i + 1][j + 1] == '-') || \
			(map[i - 1][j - 1] == '-')))
			{
				free_game(game, false);
				exit(error("Error\nThe map is not closed diagonally\n"));
			}
			j++;
		}
		i++;
	}
}

int	map_isvalid(t_game *game)
{
	if (check_valid_chars(game->map->map_clean) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (perimeter_isvalid(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
