/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:54:19 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 12:23:11 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*extract_tex_helper(t_game *game, char *str_raw)
{
	char	*tex;
	char	**str_spl;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	str_spl = ft_split(str_raw, ' ');
	if (str_spl == NULL || *str_spl[0] == ' ')
		return (NULL);
	check_if_path(game, str_spl);
	while (str_spl[1][len] != '\0' && str_spl[1][len] != ' ')
		len++;
	tex = malloc(sizeof(char) * (len + 1));
	if (tex == NULL)
		return (NULL);
	while (--len > 0)
		tex[j++] = str_spl[1][i++];
	tex[j] = '\0';
	free_2d(str_spl);
	return (tex);
}

void	run_extract_c(t_game *game, int i)
{
	if (ft_strnstr(game->map->map_raw[i], "C ", \
		ft_strlen(game->map->map_raw[i])) != NULL)
	{
		if (game->tex->ceiling_found == true)
			exit (error("Error\nDuplicate textures input\n"));
		game->tex->c->rgb = extract_tex_rgb_helper(game->map->map_raw[i], "C");
		extract_rgb(game, 'C');
		if (game->tex->c->rgb != NULL)
			game->tex->ceiling_found = true;
	}
}

void	run_extract_f(t_game *game, int i)
{
	if (ft_strnstr(game->map->map_raw[i], "F ", \
		ft_strlen(game->map->map_raw[i])) != NULL)
	{
		if (game->tex->floor_found == true)
			exit (error("Error\nDuplicate textures input\n"));
		game->tex->f->rgb = extract_tex_rgb_helper(game->map->map_raw[i], "F");
		extract_rgb(game, 'F');
		if (game->tex->f->rgb != NULL)
			game->tex->floor_found = true;
	}
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
