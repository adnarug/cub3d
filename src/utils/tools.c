/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 14:23:41 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_line_count(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		exit(error("Error\n Map misconfig\n"));
	while (array[i])
		i++;
	return (i);
}

int	assign_player(t_game *game, int i, int j, int *one_pl_found)
{
	if (ft_strchr(PLAYER_POS, game->map->map_filled[i][j]) != NULL)
	{
		if (*one_pl_found == 1)
			return (EXIT_FAILURE);
		*one_pl_found = 1;
		game->player->x_pos = j + 0.5;
		game->player->y_pos = i + 0.5;
		game->player->dir = game->map->map_filled[i][j];
		game->map->map_filled[i][j] = '0';
		init_player_angle(game);
	}
	return (EXIT_SUCCESS);
}

void	extract_hex_color(t_game *game)
{
	game->tex->c->color = \
		convert_rgb_to_hex(game->tex->c->r, game->tex->c->g, game->tex->c->b);
	game->tex->f->color = \
		convert_rgb_to_hex(game->tex->f->r, game->tex->f->g, game->tex->f->b);
}

int	dup_values(char **rgb, char **split_res, int i, int j)
{
	if (j == 0)
		rgb[i - 1] = ft_strdup(split_res[0]);
	if (j != 0)
		rgb[i] = ft_strdup(split_res[0]);
	free_2d(split_res);
	i++;
	return (i);
}

void	extract_tex_rgb_helper(t_game *game, char **rgb, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i++] != '\0' && j < 3)
	{
		if (ft_isdigit(str[i]) == 1)
		{
			rgb[j] = ft_substr(str, i, iter_loop(str, i));
			i += iter_loop(str, i);
			i = check_extra_digits(game, str, i);
			if (j == 2)
				break ;
		}
		if (str[i] == ',')
		{
			if (rgb[j] == NULL)
				error_free_prs_exit(game, "Error\nRGB misconfig1\n");
			j++;
		}
	}
}
