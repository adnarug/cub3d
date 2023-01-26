/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:05:45 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/26 14:18:27 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	check_abbr(char *str)
{
	if ((ft_strncmp(str, "NO", 2) == 0) || (ft_strncmp(str, "SO", 2) == 0) || \
		(ft_strncmp(str, "EA", 2) == 0) || (ft_strncmp(str, "WE", 2) == 0))
		return (0);
	else
		return (1);
}

void	check_if_path(t_game *game, char *str_spl)
{
	if (str_spl && ft_strchr(str_spl, '/') == NULL)
	{
		free_game(game, false);
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	}
}

void	check_miss_tex(t_game *game)
{
	if (game->tex->ceiling_found == false || game->tex->floor_found == false)
	{
		error("Error\nMap file is misconfigured\n");
		system("leaks cub3D");
		exit (1);
	}
	if (game->tex->north_found == false || game->tex->south_found == false || \
		game->tex->south_found == false || game->tex->west_found == false)
	{
		error("Error\nMap file is misconfigured\n");
		system("leaks cub3D");
		exit (1);
	}
}

void	check_tex_ext(t_game *game, char *ext)
{
	int	len;

	len = ft_strlen(ext);
	if (ft_strncmp(game->tex->no_path + \
		ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	if (ft_strncmp(game->tex->so_path + \
	ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	if (ft_strncmp(game->tex->we_path + \
	ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	if (ft_strncmp(game->tex->ea_path + \
	ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
}

void	access_tex(t_game *game)
{
	int	fd;

	fd = open(game->tex->no_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	else
		close(fd);
	fd = open(game->tex->so_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	else
		close(fd);
	fd = open(game->tex->we_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	else
		close(fd);
	fd = open(game->tex->ea_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
	else
		close(fd);
}
