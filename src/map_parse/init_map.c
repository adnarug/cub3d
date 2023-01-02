/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:05:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/02 17:33:06 by pguranda         ###   ########.fr       */
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
	printf("linecount: %d\n", *line_count);
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		return (NULL);
	while (num_lines > 0)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL || **map == ' ')
			error("Invalid map - extra newline\n");
		num_lines--;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	init_map(t_game *game)
{
	char	**map;
	int		line_count;

	line_count = 1;
	map = read_map(game->map_path, &line_count);
	if (map == NULL)
		return (EXIT_FAILURE);
	game->map = map;
	game->tex = malloc(sizeof(t_textures));
	print_2d_array(game->map);
	printf("%s\n", extract_tex(game));
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}