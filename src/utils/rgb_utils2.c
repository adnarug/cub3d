/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:28:16 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 14:22:26 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	extract_rgb_f(t_game *game)
{
	game->tex->f->r = ft_atoi(game->tex->f->rgb[0]);
	game->tex->f->g = ft_atoi(game->tex->f->rgb[1]);
	game->tex->f->b = ft_atoi(game->tex->f->rgb[2]);
	if (game->tex->f->r > 255 || game->tex->f->g > 255 || game->tex->f->b > 255)
		exit(error("Error\n RGB value out of range\n"));
	if (game->tex->f->r < 0 || game->tex->f->g < 0 || game->tex->f->b < 0)
		exit(error("Error\n RGB value out of range\n"));
}

void	extract_rgb_c(t_game *game)
{
	game->tex->c->r = ft_atoi(game->tex->c->rgb[0]);
	game->tex->c->g = ft_atoi(game->tex->c->rgb[1]);
	game->tex->c->b = ft_atoi(game->tex->c->rgb[2]);
	if (game->tex->c->r > 255 || game->tex->c->g > 255 || game->tex->c->b > 255)
		exit(error("Error\n RGB value out of range\n"));
	if (game->tex->c->r < 0 || game->tex->c->g < 0 || game->tex->c->b < 0)
		exit(error("Error\n RGB value out of range\n"));
}

int	check_extra_digits(t_game *game, char *str, int i)
{
	while (str[i] != '\0' && str[i] != ',')
	{
		if (ft_isdigit(str[i]) == 1)
			error_free_prs_exit(game, "Error\nRGB misconfig1\n");
		i++;
	}
	return (i);
}

int	iter_loop(char *str, int i)
{
	int	len;

	len = 0;
	while (ft_isdigit(str[i + len]) == 1)
		len++;
	return (len);
}
