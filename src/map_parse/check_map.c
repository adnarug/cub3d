/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:15:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/04 18:01:40 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	horiz_check(char **map)
{
	int	i;
	int	j;
	int	len;
	char *trimmed;

	i = 0;
	j = 0;
	len = 0;
	while (map[i] != NULL)
	{
		trimmed = ft_strtrim(map[i], " ");
		len = ft_strlen(trimmed);
		printf("***\nTrimmed string:%s Len:%d", trimmed, len);
		if (trimmed[0] == '1' && trimmed[len - 2] == '1')
		{
			printf("String is: OK\n");
			i++;
		}
		else
		{
			printf("String is: BAD\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

char	*flip_col_to_row(char **map, int col, int last)
{
	int	i;
	int	j;
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

int	ver_check(char **map, int last)
{
	int		i;
	int		j;
	int		col_num;
	int		col;
	char	*flipped;
	char 	*trimmed;
	int		len;

	i = 0;
	col = 0;
	j = 0;
	col_num = ft_strlen(map[i]) - 2;
	while (col <= col_num)
	{
		flipped = flip_col_to_row(map, col, last);
		trimmed = ft_strtrim(flipped, " ");
		len = ft_strlen(trimmed);
		printf("Flipped string: %s\n", flipped);
		if (trimmed[0] == '1' && trimmed[len - 1] == '1')
		{
			printf("Flipped str is: OK\n");
			i++;
		}
		else
		{
			printf("Flipped str is: BAD\n");
			return (EXIT_FAILURE);
		}
		col++;
	}
	return (EXIT_SUCCESS);
}

int	perimeter_isvalid(t_game *game)
{
	if (ver_check(game->only_map, game->only_map_lines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (horiz_check(game->only_map) != EXIT_SUCCESS);
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map_isvalid(t_game *game)
{
	if (perimeter_isvalid(game) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
}