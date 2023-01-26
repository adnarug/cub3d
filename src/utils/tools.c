/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/26 14:00:54 by pguranda         ###   ########.fr       */
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

void	check_rgb(t_game *game)
{
	if (game->tex->c->r < 0 || game->tex->c->r > 255)
		exit(error("Error\nInvalid RGB input\n"));
	if (game->tex->c->g < 0 || game->tex->c->g > 255)
		exit(error("Error\nInvalid RGB input\n"));
	if (game->tex->c->b < 0 || game->tex->c->b > 255)
		exit(error("Error\nInvalid RGB input\n"));
	if (game->tex->f->r < 0 || game->tex->f->r > 255)
		exit(error("Error\nInvalid RGB input\n"));
	if (game->tex->f->g < 0 || game->tex->f->g > 255)
		exit(error("Error\nInvalid RGB input\n"));
	if (game->tex->f->b < 0 || game->tex->f->b > 255)
		exit(error("Error\nInvalid RGB input\n"));
}

char	**extract_tex_rgb_helper(char *str, char *tex_id)
{
	char	**rgb;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	str = ft_strnstr(str, tex_id, ft_strlen(str));
	if (str == NULL)
		return (NULL);
	while (ft_isdigit(*str) == 0)
		str++;
	rgb = ft_split(str, ',');
	if (rgb == NULL)
		return (NULL);
	return (rgb);
}
