/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:22:27 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 15:30:40 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	run_extract_tex_no(t_game *game, char *dir, int i)
{
	if ((ft_strnstr(game->map->map_raw[i], dir, \
		ft_strlen(game->map->map_raw[i]))) != NULL)
	{
		if (game->tex->north_found == true)
			exit (error("Error\nDuplicate textures input\n"));
		game->tex->no_path = extract_tex_helper(game, game->map->map_raw[i], dir);
		if (access(game->tex->no_path, F_OK | R_OK) == -1)
			exit(error("Error\nCould not access texture file(s)\n"));
		if (game->tex->no_path != NULL)
			game->tex->north_found = true;
	}
}

void	run_extract_tex_so(t_game *game, char *dir, int i)
{
	if ((ft_strnstr(game->map->map_raw[i], dir, \
		ft_strlen(game->map->map_raw[i]))) != NULL)
	{
		if (game->tex->south_found == true)
			exit(error("Error\nDuplicate textures input\n"));
		game->tex->so_path = extract_tex_helper(game, game->map->map_raw[i], dir);
		if (access(game->tex->so_path, F_OK | R_OK) == -1)
			exit(error("Error\nCould not access texture file(s)\n"));
		if (game->tex->so_path != NULL)
			game->tex->south_found = true;
	}
}

void	run_extract_tex_we(t_game *game, char *dir, int i)
{
	if ((ft_strnstr(game->map->map_raw[i], dir, \
		ft_strlen(game->map->map_raw[i]))) != NULL)
	{
		if (game->tex->west_found == true)
			exit (error("Error\nDuplicate textures input\n"));
		game->tex->we_path = extract_tex_helper(game, game->map->map_raw[i], dir);
		if (access(game->tex->we_path, F_OK | R_OK) == -1)
			exit(error("Error\nCould not access texture file(s)\n"));
		if (game->tex->we_path != NULL)
			game->tex->west_found = true;
	}
}

void	run_extract_tex_ea(t_game *game, char *dir, int i)
{
	if ((ft_strnstr(game->map->map_raw[i], dir, \
		ft_strlen(game->map->map_raw[i]))) != NULL)
	{
		if (game->tex->east_found == true)
			exit (error("Error\nDuplicate textures input\n"));
		game->tex->ea_path = extract_tex_helper(game, game->map->map_raw[i], dir);
		if (access(game->tex->ea_path, F_OK | R_OK) == -1)
			exit(error("Error\nCould not access texture file(s)\n"));
		if (game->tex->ea_path != NULL)
			game->tex->east_found = true;
	}
}

int	convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}
