/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:05:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/05 18:26:29 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* Counting the newlines */
static int	file_linecount(char *file)
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
	close (fd);
	return (linecount);
}

/* Allocates memory for a string array with the same lines as the file */
static char	**malloc_columns(char *file, int *line_count)
{
	char	**map;

	*line_count = file_linecount(file);
	if (*line_count <= 0)
		error("could not read the file, it may not exist or the path is wrong\n");
	map = malloc(sizeof(char *) * (*line_count + 1));
	if (map == NULL)
		error("malloc error, when creating the map\n");
	return (map);
}

int	find_longest(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(map[i]);
	while (map[i] != NULL)
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	max++;
	return (max);
}

/* Creating with malloc 2d array based on the map */
static char	**read_map(char *file, int *line_count)
{
	char	**map;
	int		fd;
	int		i;
	int		num_lines;

	i = 0;
	if (access(file, F_OK) == -1)
	{
		error("Error\nFile does not exist\n");
		return (NULL);
	}
	map = malloc_columns(file, line_count);
	num_lines = *line_count;
	if (map == NULL)
		return (NULL);
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		return (NULL);
	while (num_lines > 0)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			error("Invalid map\n");
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
	char c;

	i = 0;
	if (s == NULL || *s == '\n')
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
	{
		c = s[i];
		if (s[i] == '1' || s[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	find_map_start(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (ft_ismapline(map[i]) == 1)
			return (i);
		else
			i++;
	}
	return (0);
}

char **fill_spaces(t_game *game, char **map)
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

char	**dup_matrix(t_game *game)
{
	char	**new_map;
	int		i;
	int		j;
	int		written_len;
	char *string;

 	i = 0;
	j = 0;
	written_len = 0;
	new_map = malloc(sizeof(char *) * game->map->map_clean_lines + 1);
	if (new_map == NULL)
		return (NULL);
	while (game->map->map_clean[i] != NULL)
	{
		new_map[i] = ft_calloc(game->map->max_len + 1, sizeof(char));
		// new_map[i] = malloc(sizeof(char ) * game->map->max_len);
		if (new_map[i] == NULL)
			return (NULL);
		written_len = ft_strlcpy(new_map[i], game->map->map_clean[i], game->map->max_len);

		if (written_len < game->map->max_len)
		{
			written_len--;
			// printf("\nchar:%c\n", new_map[written_len]);
			while (written_len < game->map->max_len - 1)
			{
				new_map[i][written_len] = '-';
				written_len++;
		 	}
			new_map[i][written_len] = '\0';
			string = new_map[i]; //TODO: to be deleted
		}
		written_len = 0;
		i++;
	}
	// new_map[i] = NULL;
	return (new_map);
}

int	init_map(t_game *game)
{
	char	**map;
	int		line_count;

	line_count = 1;
	map = read_map(game->map->path, &line_count);
	if (map == NULL)
		return (EXIT_FAILURE);
	game->map->map_raw = map;
	game->map->map_clean_start = find_map_start(game->map->map_raw);
	extract_tex(game);
	game->map->map_clean = game->map->map_raw + game->map->map_clean_start;
	game->map->max_len = find_longest(game->map->map_clean);
	game->map->map_clean_lines = ft_line_count(game->map->map_clean);
	game->map->map_filled = dup_matrix(game); 
	game->map->map_filled = fill_spaces(game, game->map->map_filled);
	if (map_isvalid(game) == EXIT_FAILURE)
		printf("Map is invalid\n");
	print_2d_array(game->map->map_filled);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}