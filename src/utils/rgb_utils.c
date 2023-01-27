/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:26:59 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/27 19:37:17 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	**init_rgb(t_game *game)
{
	char	**rgb;

	rgb = malloc(sizeof(char *) * 4);
	if (rgb == NULL)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	rgb[0] = NULL;
	rgb[1] = NULL;
	rgb[2] = NULL;
	rgb[3] = NULL;
	return (rgb);
}

void	check_rgb_valid_char(t_game *game, char *rgb)
{
	int		i;
	bool	digit_found;
	bool	one_number;

	i = 0;
	digit_found = false;
	one_number = false;
	while (rgb[i] != '\0')
	{
		if (ft_isdigit(rgb[i]) == 1)
			digit_found = true;
		if (ft_isdigit(rgb[i]) != 1 && rgb[i] != ' '
			&& rgb[i] != ',' && rgb[i] != '\t' && rgb[i] != '\n')
			error_free_prs_exit(game, "Error\nRGB misconfig1\n");
		if (rgb[i + 1] != '\0' && rgb[i] == ' ' && ft_isdigit(rgb[i + 1]) == 1)
			error_free_prs_exit(game, "Error\nRGB misconfig1\n");
		i++;
	}
	if (digit_found == false)
		error_free_prs_exit(game, "Error\nRGB misconfig2\n");
}

void	check_rgb_null(t_game *game, char **rgb)
{
	int	i;
	int	no_commas;

	no_commas = 0;
	i = 0;
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
		error_free_prs_exit(game, "Error\nRGB misconfig3\n");
	check_rgb_valid_char(game, rgb[0]);
	check_rgb_valid_char(game, rgb[1]);
	check_rgb_valid_char(game, rgb[2]);
}

void	check_commas(t_game *game, char **rgb)
{
	int	i;
	int	j;
	int	no_commas;

	no_commas = 0;
	i = 1;
	j = 0;
	while (rgb[i] != NULL)
	{
		j = 0;
		check_rgb_valid_char(game, rgb[i]);
		while (rgb[i][j] != '\0')
		{
			if (rgb[i][j] == ',')
				no_commas++;
			j++;
		}
		i++;
	}
	if (no_commas != 2)
		error_free_prs_exit(game, "Error\nRGB misconfig7\n");
}

void	check_rgb(t_game *game)
{
	if (game->tex->c->r < 0 || game->tex->c->r > 255)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	if (game->tex->c->g < 0 || game->tex->c->g > 255)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	if (game->tex->c->b < 0 || game->tex->c->b > 255)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	if (game->tex->f->r < 0 || game->tex->f->r > 255)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	if (game->tex->f->g < 0 || game->tex->f->g > 255)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	if (game->tex->f->b < 0 || game->tex->f->b > 255)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
}