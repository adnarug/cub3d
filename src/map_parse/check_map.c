/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:15:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/05 18:16:30 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define DEBUG 0
#include "../../include/cub3D.h"

int	check_holes(char *s)
{
	int	i;

	i = 0;
	if (DEBUG == 1)
	 printf("stirng to check %s\n", s);
	if (s[0] == '0')
		return (EXIT_FAILURE);
	while (s[i] != '\0')
	{
		if (s[i] == '0')
		{
			if (i > 0 && ((s[i - 1] == '-') || (s[i + 1] == '-')))
			{
				if (DEBUG == 1)
					printf("Failed trimmed: %s\n", s);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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
		trimmed = ft_strtrim(map[i], "-");
		len = ft_strlen(trimmed);
		if (check_holes(trimmed) == EXIT_FAILURE)
		{
			if (DEBUG == 1)
				printf("Failed trimmed: %s\n", trimmed);
			return (EXIT_FAILURE);
		}
		else
			i++;
		free(trimmed);
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
		printf("i:%d col:%d\n", i, col);
		flipped[i] = map[i][col];//TODO:seg here
		i++;
		last--;
	}
	flipped[i] = '\0';
	return (flipped);
}

// int check_wall_integrity(char *s)
// {
// 	int	i;
// 	int	flag_open_wall;
// 	int	flag_close_wall;
	
// 	i = 0;
// 	flag_open_wall = 0;
// 	flag_close_wall = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == '1')
// 		{
// 			if (flag_open_wall == 1)
// 				flag_close_wall == 0;
// 			else
// 				flag_open_wall = 1;
// 		}
// 		i++;
// 	}
// }

int	ver_check(t_game *game, char **map, int last)
{
	int		col_num;
	int		col;
	char	*flipped;
	char 	*trimmed;
	int		len;

	col = 0;
	col_num = game->map->max_len;//TODO: ned to find the longest line first
	while (col <= col_num)
	{
		flipped = flip_col_to_row(map, col, last);
		trimmed = ft_strtrim(flipped, "-");
		len = ft_strlen(trimmed);
		if (check_holes(trimmed) == EXIT_FAILURE)
		{
			if (DEBUG == 1)
				printf("Failed flipped: %s\n", trimmed);
			return (EXIT_FAILURE);
		}
		else
			col++;
		// if (trimmed[0] == '1' && trimmed[len - 1] == '1')
		// {
		// 	printf("Flipped string - OK flipped : %s trimmed: %s\n", flipped, trimmed);
		// 	col++;
		// }
		// else
		// {
		// 	if (DEBUG == 1)
		// 		printf("Flipped string - BAD flipped : %s trimmed: %s\n", flipped, trimmed);
		// 	free(flipped);
		// 	free(trimmed);
		// 	return (EXIT_FAILURE);
		// }
		free(flipped);
		free(trimmed);
	}
	return (EXIT_SUCCESS);
}


int	perimeter_isvalid(t_game *game)
{
	// if (ft_strchr(game->map->map_filled[0], '0') != NULL \
	// || ft_strchr(game->map->map_filled[game->map->map_clean_lines], '0') != NULL)
	// 	return (EXIT_FAILURE);
	if (ver_check(game, game->map->map_filled, game->map->map_clean_lines) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (horiz_check(game->map->map_filled) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (check_holes(game->map->map_filled) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map_isvalid(t_game *game)
{
	if (perimeter_isvalid(game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}