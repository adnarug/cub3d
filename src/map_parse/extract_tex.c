/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:50:32 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 13:22:26 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	extract_rgb_f(t_game *game, char c)
{
	game->tex->f->r = ft_atoi(game->tex->f->rgb[0]);
	game->tex->f->g = ft_atoi(game->tex->f->rgb[1]);
	game->tex->f->b = ft_atoi(game->tex->f->rgb[2]);
	if (game->tex->f->r > 255 || game->tex->f->g > 255 || game->tex->f->b > 255)
		exit(error("Error\n RGB value out of range\n"));
	if (game->tex->f->r < 0 || game->tex->f->g < 0 || game->tex->f->b < 0)
		exit(error("Error\n RGB value out of range\n"));
}

void	extract_rgb_c(t_game *game, char c)
{
	game->tex->c->r = ft_atoi(game->tex->c->rgb[0]);
	game->tex->c->g = ft_atoi(game->tex->c->rgb[1]);
	game->tex->c->b = ft_atoi(game->tex->c->rgb[2]);
	if (game->tex->c->r > 255 || game->tex->c->g > 255 || game->tex->c->b > 255)
		exit(error("Error\n RGB value out of range\n"));
	if (game->tex->c->r < 0 || game->tex->c->g < 0 || game->tex->c->b < 0)
		exit(error("Error\n RGB value out of range\n"));
}

static void	load_textures(t_game *game)
{
	xpm_t	*no_xpm;
	xpm_t	*so_xpm;
	xpm_t	*ea_xpm;
	xpm_t	*we_xpm;

	no_xpm = mlx_load_xpm42(game->tex->no_path);
	game->tex->no = no_xpm;
	so_xpm = mlx_load_xpm42(game->tex->so_path);
	game->tex->so = so_xpm;
	ea_xpm = mlx_load_xpm42(game->tex->ea_path);
	game->tex->ea = ea_xpm;
	we_xpm = mlx_load_xpm42(game->tex->we_path);
	game->tex->we = we_xpm;
}

void	check_n_extract(t_game *game, char **str, char *one_str)
{
	if (ft_strncmp (str[0], "NO", 2) == 0)
		run_extract_tex_no(game, str[1]);
	if (ft_strncmp (str[0], "SO", 2) == 0)
		run_extract_tex_so(game, str[1]);
	if (ft_strncmp (str[0], "WE", 2) == 0)
		run_extract_tex_we(game, str[1]);
	if (ft_strncmp (str[0], "EA", 2) == 0)
		run_extract_tex_ea(game, str[1]);
	if (ft_strncmp (str[0], "F", 1) == 0)
		run_extract_f(game, str, one_str);
	if (ft_strncmp (str[0], "C", 1) == 0)
		run_extract_c(game, str, one_str);
}

void	run_extraction(t_game *game)
{
	int		j;
	char	**str_spl;

	j = 0;
	while (j < game->map->map_clean_start)
	{
		str_spl = ft_split(game->map->map_raw[j], ' ');
		game->tex->raw_path = str_spl;
		if (str_spl && str_spl[0] && ft_isalnum(*str_spl[0]) == 1)
			check_n_extract(game, str_spl, game->map->map_raw[j]);
		j++;
		free_2d(str_spl);
	}
	rgb_check(game);
}

char	*extract_tex(t_game *game)
{
	wrong_key_tex(game);
	run_extraction(game);
	check_miss_tex(game);
	check_tex_ext(game, ".xpm42");
	load_textures(game);
	return (NULL);
}
