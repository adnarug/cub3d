/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/27 17:49:26 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_line_count(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
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

void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

char	**extract_tex_rgb_helper(t_game *game, char **str)
{
	char	**rgb;
	char	**split_res;
	int		i;
	int		j;

	i = 1;
	j = 0;
	rgb = malloc(sizeof(char *) * 4);
	if (rgb == NULL)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	init_rgb(rgb);
	check_commas(game, str);
	while (i < 4 && str[i] != NULL)
	{
		check_rgb_valid_char(game, str[i]);
		split_res = ft_split(str[i], ',');
		if (split_res == NULL)
			error_free_prs_exit(game, "Error\nRGB misconfig\n");
		if (ft_line_count(split_res) == 1)
		{
			if (j == 0)
				rgb[i - 1] = ft_strdup(split_res[0]);
			if (j != 0)
				rgb[i] = ft_strdup(split_res[0]);
			free_2d(split_res);
			i++;
		}
		else
		{
			while (split_res[j] != NULL)
			{
				rgb[i - 1] = ft_strdup(split_res[j]);
				j++;
				i++;
			}
			if (i - 1 != 3)
				i = j;
			free_2d(split_res);
		}	
	}
	check_rgb_null(game, rgb);
	return (rgb);
}
