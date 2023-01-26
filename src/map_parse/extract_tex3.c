/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:54:19 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/26 13:06:45 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	check_validity(char *to_check)
{
	int	i;
	char *valid_keys[8];

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
			return (EXIT_SUCCESS) ;
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
		if (str_spl && str_spl[0] && ft_isalnum(*str_spl[0]) == 1)
		{
			if (check_validity(str_spl[0]) == EXIT_FAILURE)
			{
				free_2d(str_spl);
				error_free_prs_exit(game, "Error\nMap file is misconfigured\n");
			}
		}
		free_2d(str_spl);
		j++;
	}
	return (EXIT_SUCCESS);
}

char	*extract_tex_helper(t_game *game, char *str_raw, char *dir)
{
	char	*tex;
	char	**str_spl;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	// str_spl = ft_split(str_raw, ' ');

	// if (str_spl == NULL || *str_spl[0] == ' ')
	// 	return (NULL);
	// printf("str_spl%s dir%s\n", str_spl[0], dir);
	// if (ft_strncmp(dir, str_spl[0], 2) != 0)
	// 	error("Warning\nPotential misconfig of textures\n");
	check_if_path(game, str_raw);
	while (str_raw[len] != '\0' && str_raw[len] != ' ')
		len++;
	tex = malloc(sizeof(char) * (len + 1));
	if (tex == NULL)
		return (NULL);
	while (--len > 0)
		tex[j++] = str_raw[i++];
	tex[j] = '\0';
	// free_2d(str_spl);
	return (tex);
}

void	run_extract_c(t_game *game, char **str)
{
		if (game->tex->ceiling_found == true)
			error_free_prs_exit(game, "Error\nDuplicate textures input\n");
		game->tex->c->rgb = str;
		extract_rgb(game, 'C');
		if (game->tex->c->rgb != NULL)
			game->tex->ceiling_found = true;
}

void	run_extract_f(t_game *game, char **str)
{
	if (game->tex->floor_found == true)
		error_free_prs_exit(game, "Error\nDuplicate textures input\n");
	game->tex->f->rgb = str;
	extract_rgb(game, 'F');
	if (game->tex->f->rgb != NULL)
		game->tex->floor_found = true;
}

char	**extract_tex_rgb_helper(t_game *game, char *str, char *tex_id)
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
	return (rgb);
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
