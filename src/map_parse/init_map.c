/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:05:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 16:48:08 by pguranda         ###   ########.fr       */
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
static char	**malloc_rows(char *file, int *line_count)
{
	char	**map;

	*line_count = file_linecount(file);
	if (*line_count <= 0)
		error("could not read the file, it may not exist or the path is wrong\n");
	map = malloc(sizeof(char *) * (*line_count + 1));
	if (map == NULL)
		exit (1);
	return (map);
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
	int pos_max;

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
	int	i;
	int	max;
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
		error("Error\n File does not exist / not accessible\n");
		exit (1);
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
		if (DEBUG == 1)
			printf("max len %d written len %d last char %c \n", game->map->max_len, written_len, new_map[i][written_len - 1]);
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
/*A direction vector can be seen as follows: if you draw a line in the direction 
the player looks, through the position of the player, 
then every point of the line is the sum of the position of the player, 
and a multiple of the direction vector
*/
/*Angles in rad, 1 rad = 57 degrees*/
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
	char	**map;
	int		one_pl_found;
	
	i = 0;
	j = 0;
	one_pl_found = 0;
	map = game->map->map_filled;
	while(map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(PLAYER_POS, map[i][j]) != NULL)
			{
				if (one_pl_found == 1)
					return (EXIT_FAILURE);
				one_pl_found = 1;
				game->player->x_pos = j + 0.5;
				game->player->y_pos = i + 0.5;
				game->player->dir = map[i][j];
				map[i][j] =  '0';
				init_player_angle(game);
			}
			j++;
		}
		i++;
	}
	if (one_pl_found == 1)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}


int	init_map(t_game *game)
{

	int		line_count;
	char	**clean_map;

	line_count = 1;
	clean_map = NULL;
	game->map->map_raw = read_map(game->map->path, &line_count);
	if (game->map->map_raw == NULL)
		return (EXIT_FAILURE);
	game->map->map_clean_start = find_map_start(game->map->map_raw);
	if (game->map->map_clean_start == 0)
		exit(error("Error\n The map file is incomplete\n"));
	game->map->map_clean = game->map->map_raw + game->map->map_clean_start;
	extract_tex(game);
	game->map->max_len = find_longest(game->map->map_clean);
	// replace_nl(game, game->map->map_clean);
	game->map->map_clean_lines = ft_line_count(game->map->map_clean);
	game->map->map_filled = dup_matrix(game);
	game->map->map_filled = fill_spaces(game, game->map->map_filled);
	if (DEBUG == 1)
	{
		print_2d_array(game->map->map_filled);
		// printf("Starting position - x: %f y: %f\n", game->player->x_pos, game->player->y_pos);
	}
	if (find_player(game) == EXIT_FAILURE)
	{
		error("Error\nInvalid map\n");
		exit(1);
	}
	if (map_isvalid(game) == EXIT_FAILURE)
	{
		error("Error\nMap is invalid\n");
		exit(1);
	}
	check_diag_hole(game);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}