/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:50:20 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/26 13:42:55 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_player_angle(t_game *game)
{
	if (game->player->dir == 'N')
		game->player->angle = 0;
	else if (game->player->dir == 'S')
		game->player->angle = M_PI;
	else if (game->player->dir == 'W')
		game->player->angle = 1.5 * M_PI;
	else if (game->player->dir == 'E')
		game->player->angle = 0.5 * M_PI;
	game->player->x_scalar = sin(game->player->angle);
	game->player->y_scalar = -1 * cos(game->player->angle);
	init_camera_plane(game);
}

int	find_player(t_game *game)
{
	int		i;
	int		j;
	int		one_pl_found;

	i = 0;
	one_pl_found = 0;
	while (game->map->map_filled[i] != NULL)
	{
		j = 0;
		while (game->map->map_filled[i][j] != '\0')
		{
			if (assign_player(game, i, j, &one_pl_found) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	if (one_pl_found == 1)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	find_map_start(char **map)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = NULL;
	while (map[i] != NULL)
	{
		trimmed = ft_strtrim(map[i], " ");
		if (ft_ismapline(trimmed) == 1)
		{
			free(trimmed);
			trimmed = NULL;
			return (i);
		}
		else
			i++;
		free(trimmed);
		trimmed = NULL;
	}
	return (0);
}

char	**fill_spaces(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map->map_clean_lines)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ' ')
				map[i][j] = '-';
			j++;
		}
		j = 0;
		i++;
	}
	return (map);
}

int	check_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(VALID_CHAR, map[i][j]) == NULL)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
