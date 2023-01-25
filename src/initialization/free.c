/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:47:36 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 12:21:45 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	free_2d(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

int	free_game(t_game *game, bool img_flag)
{
	free_2d(game->tex->f->rgb);
	free_2d(game->tex->c->rgb);
	free(game->tex->f);
	free(game->tex->c);
	free(game->tex->no_path);
	free(game->tex->so_path);
	free(game->tex->we_path);
	free(game->tex->ea_path);
	mlx_delete_xpm42(game->tex->no);
	mlx_delete_xpm42(game->tex->so);
	mlx_delete_xpm42(game->tex->we);
	mlx_delete_xpm42(game->tex->ea);
	free(game->tex);
	free_2d(game->map->map_raw);
	free_2d(game->map->map_filled);
	free(game->map);
	if (img_flag == true)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_delete_image(game->mlx, game->mini->img);
		free(game->mini);
	}
	free(game->player);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
