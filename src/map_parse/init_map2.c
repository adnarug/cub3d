/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:25:44 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 11:32:18 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	copy_map(t_game *game, char **new_map, int i)
{
	int	written_len;

	written_len = 0;
	new_map[i] = ft_calloc(game->map->max_len + 1, sizeof(char));
	if (new_map[i] == NULL)
		(exit(1));
	written_len = ft_strlcpy(new_map[i], \
		game->map->map_clean[i], game->map->max_len);
	if (written_len < game->map->max_len)
	{
		if (i != game->map->map_clean_lines - 1)
			written_len--;
		while (written_len < game->map->max_len - 1)
		{
			new_map[i][written_len] = '-';
			written_len++;
		}
		new_map[i][written_len] = '\0';
	}
}

char	**dup_matrix(t_game *game)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (game->map->map_clean_lines + 1));
	if (new_map == NULL)
		return (NULL);
	while (game->map->map_clean[i] != NULL)
	{
		copy_map(game, new_map, i);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

/* Allocates memory for a string array with the same lines as the file */
static char	**malloc_rows(char *file, int *line_count)
{
	char	**map;

	*line_count = file_linecount(file);
	if (*line_count <= 0)
	{
		error("Error\ncould not read the file\n");
		exit(1);
	}
	map = malloc(sizeof(char *) * (*line_count + 1));
	if (map == NULL)
		exit (1);
	return (map);
}

char	**read_map(t_game *game, char *file, int *line_count)
{
	char	**map;
	int		fd;
	int		i;
	int		num_lines;

	i = 0;
	map = malloc_rows(file, line_count);
	num_lines = *line_count;
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		error_free_f_exit(game, "Error\n File does not exist / not accessible\n");
	while (num_lines > 0)
	{
		map[i] = get_next_line(fd);
		num_lines--;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	ft_ismapline(char *s)
{
	int	i;

	i = 0;
	if (s == NULL || *s == '\n')
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
	{
		if (ft_isdigit(s[i]) == 1 || s[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}
