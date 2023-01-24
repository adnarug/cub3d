/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:15:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 16:59:42 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_holes(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '0')
		return (EXIT_FAILURE);
	while (s[i] != '\0')
	{
		if (s[i] == '0')
		{
			if (i > 0 && (s[i - 1] == '-' || s[i + 1] == '-'))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	horiz_check(char **map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (map[i] != NULL)
	{
		if (check_holes(map[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

static char	*flip_col_to_row(char **map, int col, int last)
{
	int		i;
	int		j;
	char	*flipped;

	i = 0;
	j = 0;
	flipped = malloc(sizeof(char) * (last + 1));
	if (flipped == NULL)
		return (NULL);
	while (last > 0)
	{
		flipped[i] = map[i][col];
		i++;
		last--;
	}
	flipped[i] = '\0';
	return (flipped);
}

static int	ver_check(t_game *game, char **map, int last)
{
	int		col_num;
	int		col;
	char	*flipped;

	col = 0;
	col_num = game->map->max_len;
	while (col <= col_num)
	{
		flipped = flip_col_to_row(map, col, last);
		if (check_holes(flipped) == EXIT_FAILURE)
		{
			free(flipped);
			return (EXIT_FAILURE);
		}
		else
			col++;
		free(flipped);
	}
	return (EXIT_SUCCESS);
}

int	perimeter_isvalid(t_game *game)
{
	if (ft_strchr(game->map->map_filled[game->map->map_clean_lines - 1], '0') \
		!= NULL)
		return (EXIT_FAILURE);
	if (ver_check(game, game->map->map_filled, game->map->map_clean_lines) \
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (horiz_check(game->map->map_filled) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
