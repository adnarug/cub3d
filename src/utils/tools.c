/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 11:31:30 by pasha            ###   ########.fr       */
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
void print_2d(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

char	**extract_tex_rgb_helper(t_game *game, char **d_str, char *str)
{
	char **rgb;
	int i;
	int	j;
	int len;
	
	i = 0;
	j = 0;
	check_commas(game, d_str);
	rgb = malloc(sizeof(char *) * 4);
	rgb[0] = NULL;
	rgb[1] = NULL;
	rgb[2] = NULL;
	rgb[3] = NULL;
	if (rgb == NULL)
		error_free_prs_exit(game, "Error\nRGB misconfig\n");
	while (str[i] != '\0' && j < 3)
	{
		printf("c %s\n", str);
		if (ft_isdigit(str[i]) == 0)
			i++;
		if (ft_isdigit(str[i]) == 1)
		{
			len = 0;
			while (ft_isdigit(str[i + len]) == 1)
				len++;
			rgb[j] = ft_substr(str, i, len);
		
		printf("res %s j: %d\n", rgb[j], j);
			i += len;
			
		while (str[i] != '\0' && str[i] != ',')
		{
			if(ft_isdigit(str[i]) == 1)
				error_free_prs_exit(game, "Error\nRGB misconfig2\n");
			i++;
		}
		if (j == 2)
			break ;
		}
		if (str[i] == ',')
		{
			if (rgb[j] == NULL)
				error_free_prs_exit(game, "Error\nRGB misconfig5\n");
			j++;
		}
		i++;
	}
	printf("check\n");
	check_rgb_null(game, rgb);
	print_2d(rgb);
	return (rgb);
}
// char	**extract_tex_rgb_helper(t_game *game, char **str)
// {
// 	char	**rgb;
// 	char	**split_res;
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	rgb = init_rgb(game);
// 	check_commas(game, str);
// 	while (i < 4 && str[i] != NULL)
// 	{
// 		split_res = ft_split(str[i], ',');
// 		if (ft_line_count(split_res) == 1)
// 			i = dup_values(rgb, split_res, i, j);
// 		else
// 		{
// 			while (split_res[j] != NULL)
// 				rgb[i++ - 1] = ft_strdup(split_res[j++]);
// 			if (i - 1 != 3)
// 				i = j;
// 			free_2d(split_res);
// 		}	
// 	}
// 	check_rgb_null(game, rgb);
// 	return (rgb);
// }
