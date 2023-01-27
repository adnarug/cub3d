/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:26:59 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/27 13:27:59 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_rgb(char **rgb)
{
	rgb[0] = NULL;
	rgb[1] = NULL;
	rgb[2] = NULL;
	rgb[3] = NULL;
}

void	check_rgb_valid_char(char *rgb)
{
	int		i;
	bool	digit_found;

	i = 0;
	digit_found = false;
	while (rgb[i] != '\0')
	{
		if (ft_isdigit(rgb[i]) == 1)
			digit_found = true;
		if (ft_isdigit(rgb[i]) != 1 && rgb[i] != ' '
			&& rgb[i] != ',' && rgb[i] != '\t' && rgb[i] != '\n')
			exit(error("Error\nRGB misconfig\n"));
		i++;
	}
	if (digit_found == false)
		exit(error("Error\nRGB misconfig\n"));
}

void	check_rgb_null(char **rgb)
{
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
		exit(error("Error\nRGB misconfig\n"));
	check_rgb_valid_char(rgb[0]);
	check_rgb_valid_char(rgb[1]);
	check_rgb_valid_char(rgb[2]);
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
