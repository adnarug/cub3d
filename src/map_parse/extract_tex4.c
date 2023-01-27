/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:22:27 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/27 11:54:27 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	run_extract_tex_no(t_game *game, char *str)
{
	int	fd;

	if (game->tex->north_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->no_path = extract_tex_helper(game, str);
	fd = open(game->tex->no_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nCould not access texture file1(s)\n");
	else
		close(fd);
	if (game->tex->no_path != NULL)
		game->tex->north_found = true;
}

void	run_extract_tex_so(t_game *game, char *str)
{
	int	fd;

	if (game->tex->south_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->so_path = extract_tex_helper(game, str);
	fd = open(game->tex->so_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nCould not access texture file2(s)\n");
	else
		close(fd);
	if (game->tex->so_path != NULL)
		game->tex->south_found = true;
}

void	run_extract_tex_we(t_game *game, char *str)
{
	int	fd;

	if (game->tex->west_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->we_path = extract_tex_helper(game, str);
	fd = open(game->tex->we_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nCould not access texture fil3e(s)\n");
	else
		close(fd);
	if (game->tex->we_path != NULL)
		game->tex->west_found = true;
}

void	run_extract_tex_ea(t_game *game, char *str)
{
	int	fd;

	if (game->tex->east_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->ea_path = extract_tex_helper(game, str);
	fd = open(game->tex->ea_path, O_RDONLY);
	if (fd < 0)
		error_free_prs_exit(game, "Error\nCould not access texture file4(s)\n");
	else
		close(fd);
	if (game->tex->ea_path != NULL)
		game->tex->east_found = true;
}

int	convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}
