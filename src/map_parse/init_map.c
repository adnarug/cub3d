/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:05:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/06 17:37:05 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG 1
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
static char	**malloc_rows(char *file, int *line_count)
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
	map = malloc_rows(file, line_count);
	num_lines = *line_count;
	if (map == NULL)
		return (NULL);
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		return (NULL);
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
/*TODO: Handling the \n */
char	**dup_matrix(t_game *game)
{
	char	**new_map;
	int		i;
	int		j;
	int		written_len;

 	i = 0;
	j = 0;
	written_len = 0;
	new_map = malloc(sizeof(char *) * (game->map->map_clean_lines + 1));
	if (new_map == NULL)
		return (NULL);
	while (game->map->map_clean[i] != NULL)
	{
		new_map[i] = ft_calloc(game->map->max_len + 1, sizeof(char));
		if (new_map[i] == NULL)
			return (NULL);
		written_len = ft_strlcpy(new_map[i], game->map->map_clean[i], game->map->max_len);
		if (written_len < game->map->max_len)
		{
			written_len--;
			while (written_len < game->map->max_len)
			{
				new_map[i][written_len] = '-';
				written_len++;
		 	}
			written_len++;
			new_map[i][written_len] = '\0';
		}
		written_len = 0;
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	check_valid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(VALID_CHAR, map[i][j]) == NULL)
			{
				if (DEBUG == 1)
					printf("Invalid chars found in: %s it is: %c\n", map[i], map[i][j]);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


int	init_map(t_game *game)
{
	char	**map;
	int		line_count;
	char	**clean_map;

	line_count = 1;
	clean_map = NULL;
	map = read_map(game->map->path, &line_count);
	if (map == NULL)
		return (EXIT_FAILURE);
	game->map->map_raw = map;
	game->map->map_clean_start = find_map_start(game->map->map_raw);
	game->map->map_clean = game->map->map_raw + game->map->map_clean_start;
	extract_tex(game);
	game->map->max_len = find_longest(game->map->map_clean);
	game->map->map_clean_lines = ft_line_count(game->map->map_clean);
	game->map->map_filled = dup_matrix(game); 
	game->map->map_filled = fill_spaces(game, game->map->map_filled);
	if (map_isvalid(game) == EXIT_FAILURE)
		error("Error\nMap is invalid\n");
	if (DEBUG == 1)
		print_2d_array(game->map->map_filled);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}