/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:54:19 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/27 11:37:29 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	check_validity(char *to_check)
{
	int		i;
	char	*valid_keys[8];

	i = 0;
	valid_keys[0] = "NO";
	valid_keys[1] = "SO";
	valid_keys[2] = "EA";
	valid_keys[3] = "WE";
	valid_keys[4] = "C";
	valid_keys[5] = "F";
	valid_keys[7] = NULL;
	while (valid_keys[i] != NULL)
	{
		if (ft_strncmp(to_check, valid_keys[i], 2) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	wrong_key_tex(t_game *game)
{
	int		j;
	char	**str_spl;

	j = 0;
	while (j < game->map->map_clean_start)
	{
		str_spl = ft_split(game->map->map_raw[j], ' ');
		game->tex->raw_path = str_spl;
		if (str_spl && str_spl[0] && ft_isalnum(*str_spl[0]) == 1)
		{
			if (check_validity(str_spl[0]) == EXIT_FAILURE)
				error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
		}
		free_2d(str_spl);
		j++;
	}
	return (EXIT_SUCCESS);
}

char	*extract_tex_helper(t_game *game, char *str_raw)
{
	char	*tex;
	int		i;
	int		j;
	int		len;

	j = 0;
	i = 0;
	len = 0;
	check_if_path(game, str_raw);
	while (str_raw[len] != '\0' && str_raw[len] != ' ')
		len++;
	tex = malloc(sizeof(char) * (len + 1));
	if (tex == NULL)
		return (NULL);
	while (--len > 0)
		tex[j++] = str_raw[i++];
	tex[j] = '\0';
	return (tex);
}

void	run_extract_c(t_game *game, char **str)
{
	if (game->tex->ceiling_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->c->rgb = extract_tex_rgb_helper(str);
	// if (ft_line_count(str) != 3)
	// {
	// 	printf("LINES: %d\n", ft_line_count(str));
	// 	error_free_prs_exit(game, "Error\nMisconfigured textures\n");
	// }
	extract_rgb(game, 'C');	
	printf("ints: %d %d %d\n", game->tex->c->r, game->tex->c->g, game->tex->c->b);
	if (game->tex->c->rgb != NULL)
		game->tex->ceiling_found = true;
}

void	run_extract_f(t_game *game, char **str)
{
	if (game->tex->floor_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->f->rgb = extract_tex_rgb_helper(str);
	// if (ft_line_count(str) != 3)
	// {
	// 	printf("LINES: %d\n", ft_line_count(str));
	// 	error_free_prs_exit(game, "Error\nMisconfigured textures\n");
	// }
	extract_rgb(game, 'F');
	printf("ints: %d %d %d\n", game->tex->f->r, game->tex->f->g, game->tex->f->b);
	if (game->tex->f->rgb != NULL)
		game->tex->floor_found = true;
}
