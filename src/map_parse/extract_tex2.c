/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:05:45 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 17:36:43 by jtsizik          ###   ########.fr       */
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

void	check_if_path(t_game *game, char **str_spl)
{
	if (check_abbr(str_spl[0]) != 0 || \
	(ft_strchr(str_spl[1], '/') == NULL))
	{
		free_game(game, false);
		exit(error("Error\nTextures input is incorrect\n"));
	}
}

void	check_miss_tex(t_game *game)
{
	if (game->tex->ceiling_found == false || game->tex->floor_found == false)
		exit(error("Error\nSome texture(s) missing\n"));
	if (game->tex->north_found == false || game->tex->south_found == false || \
		game->tex->south_found == false || game->tex->west_found == false)
		exit(error("Error\nSome texture(s) missing\n"));
}

void	check_tex_ext(t_game *game, char *ext)
{
	int	len;

	len = ft_strlen(ext);
	if (ft_strncmp(game->tex->no_path + \
		ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
	if (ft_strncmp(game->tex->so_path + \
	ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
	if (ft_strncmp(game->tex->we_path + \
	ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
	if (ft_strncmp(game->tex->ea_path + \
	ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
}

void	access_tex(t_game *game)
{
	int	fd;

	fd = open(game->tex->no_path, O_RDONLY);
	if (fd < 0)
		exit(error("Error\nCould not access texture file(s)\n"));
	else
		close(fd);
	fd = open(game->tex->so_path, O_RDONLY);
	if (fd < 0)
		exit(error("Error\nCould not access texture file(s)\n"));
	else
		close(fd);
	fd = open(game->tex->we_path, O_RDONLY);
	if (fd < 0)
		exit(error("Error\nCould not access texture file(s)\n"));
	else
		close(fd);
	fd = open(game->tex->ea_path, O_RDONLY);
	if (fd < 0)
		exit(error("Error\nCould not access texture file(s)\n"));
	else
		close(fd);
}
