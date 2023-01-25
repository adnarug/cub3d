/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:05:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 12:54:41 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	file_linecount(char *file)
{
	int		linecount;
	int		fd;
	int		readcount;
	char	c;	

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 1;
	while (1)
	{
		readcount = read(fd, &c, 1);
		if (readcount == 0)
			break ;
		if (readcount < 0)
			return (-1);
		if (c == '\n')
			linecount++;
	}
	close(fd);
	return (linecount);
}

int	ft_strlen_nl(const char *c)
{
	size_t				i;

	i = 0;
	while (c[i] != '\0' && c[i] != '\n')
		i++;
	return (i);
}

int	find_longest(char **map)
{
	int	i;
	int	max;
	int	pos_max;

	i = 0;
	pos_max = 0;
	max = ft_strlen(map[i]);
	while (map[i] != NULL)
	{
		if (max < ft_strlen_nl(map[i]))
		{
			max = ft_strlen_nl(map[i]);
			pos_max = i;
		}
		i++;
	}
	return (max + 1);
}

void	replace_nl(t_game *game, char **map)
{
	int		i;
	int		max;
	char	*string;

	max = game->map->max_len;
	i = 0;
	while (map[i] != NULL)
	{
		if (ft_strlen(map[i]) == max)
			map[i][max - 1] = '-';
		string = map[i];
		i++;
	}
}

int	init_map(t_game *game)
{
	int		line_count;
	char	**clean_map;

	line_count = 1;
	clean_map = NULL;
	game->map->map_raw = read_map(game, game->map->path, &line_count);
	if (game->map->map_raw == NULL)
		return (EXIT_FAILURE);
	game->map->map_clean_start = find_map_start(game->map->map_raw);
	if (game->map->map_clean_start == 0)
		exit(error("Error\n The map file is incomplete\n"));
	game->map->map_clean = game->map->map_raw + game->map->map_clean_start;
	extract_tex(game);
	game->map->max_len = find_longest(game->map->map_clean);
	game->map->map_clean_lines = ft_line_count(game->map->map_clean);
	game->map->map_filled = dup_matrix(game);
	game->map->map_filled = fill_spaces(game, game->map->map_filled);
	if (find_player(game) == EXIT_FAILURE)
		error_free_f_exit(game, "Error\nMap is invalid\n");
	if (map_isvalid(game) == EXIT_FAILURE)
		error_free_f_exit(game, "Error\nMap is invalid\n");
	check_diag_holes(game);
	return (EXIT_SUCCESS);
}
