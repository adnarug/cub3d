/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:47:36 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/19 14:24:50 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void free_2d(char **matrix)
{
	int i;

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

int		free_game(t_game *game)
{
	
	free_2d(game->tex->f->rgb);
	free_2d(game->tex->c->rgb);
	free(game->tex->f);
	free(game->tex->c);
	free(game->tex->no);
	free(game->tex->so);
	free(game->tex->we);
	free(game->tex->ea);
	free_2d(game->tex->tex_spl);
	free(game->tex);
	free_2d(game->map->map_raw);
	free_2d(game->map->map_filled);
	free(game->map);
	return (EXIT_SUCCESS);
}
