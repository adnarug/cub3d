/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/27 12:06:01 by pguranda         ###   ########.fr       */
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

// char	**extract_tex_rgb_helper(char **str)
// {
// 	char	**rgb;
// 	char	*clean_str;
// 	int		len;
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	rgb = malloc(sizeof(char*) * 3);
// 	while (str[i] != NULL)
// 	{
// 		j = 0;
// 		rgb[i] = NULL;
// 		if (i > 2)
// 		{
// 			error("Error\nRGB misconfigured\n");
// 			exit(1);
// 		}
// 		clean_str = ft_strtrim(str[i], " ");
// 		printf("str: %s\n", clean_str);
// 		while(clean_str[j]!= '\0')
// 		{
// 			len = 0;
// 			while (ft_isdigit(clean_str[j]) == 0)
// 				j++;
// 			while (ft_isdigit(clean_str[j]) == 1)
// 			{
// 				len++;
// 				j++;
// 			}
// 			j--;
// 			printf("2: %s\n", &clean_str[j - len]);
// 			rgb[i] = malloc(sizeof(char) * len + 1);
// 			ft_strlcpy(rgb[i], &clean_str[j - len], len);
// 			printf("3: %s\n", rgb[i]);
// 			while (clean_str[j] != '\0' && clean_str[j] != ',')
// 				j++;
// 		}
// 		free(clean_str);
// 		i++;
// 	}
// 	return (rgb);
// }

void print_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	init_rgb(char **rgb)
{
	rgb[0] = NULL;
	rgb[1] = NULL;
	rgb[2] = NULL;
	rgb[3] = NULL;
}

void	check_rgb_valid_char(char *rgb)
{
	int i;
	bool	digit_found;

	i = 0;
	digit_found	= false;
	while (rgb[i] != '\0')
	{
		if (ft_isdigit(rgb[i]) == 1)
			digit_found = true;
		if (ft_isdigit(rgb[i]) != 1 && rgb[i] != ' ' && rgb[i] != ',' && rgb[i] != '\t' && rgb[i] != '\n')
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

char **extract_tex_rgb_helper(char **str)
{
	char **rgb;
	char **split_res;
	char *clean_str;
	int i;
	int j;

	i = 1;
	j = 0;
	rgb = malloc(sizeof(char*) * 4);
	if (rgb == NULL)
		exit(error("Error\nMalloc failed\n"));
	init_rgb(rgb);
	while (i < 4 && str[i] != NULL)
	{
		split_res = ft_split(str[i], ',');

		if (split_res == NULL)
			exit(error("Error\nRGB misconfig\n"));
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
		}	
		}
	check_rgb_null(rgb);
	return (rgb);
}