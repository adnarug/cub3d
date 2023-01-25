/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:50:32 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 15:38:34 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	extract_rgb(t_game *game, char c)
{
	if (c == 'F')
	{
		game->tex->f->r = ft_atoi(game->tex->f->rgb[0]);
		game->tex->f->g = ft_atoi(game->tex->f->rgb[1]);
		game->tex->f->b = ft_atoi(game->tex->f->rgb[2]);
	}
	if (c == 'C')
	{
		game->tex->c->r = ft_atoi(game->tex->c->rgb[0]);
		game->tex->c->g = ft_atoi(game->tex->c->rgb[1]);
		game->tex->c->b = ft_atoi(game->tex->c->rgb[2]);
	}
}

void	extract_hex_color(t_game *game)
{
	game->tex->c->color = \
		convert_rgb_to_hex(game->tex->c->r, game->tex->c->g, game->tex->c->b);
	game->tex->f->color = \
		convert_rgb_to_hex(game->tex->f->r, game->tex->f->g, game->tex->f->b);
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

char	*extract_tex(t_game *game)
{
	int		i;

	i = 0;
	wrong_key_tex(game);
	while (i < game->map->map_clean_start)
	{
		run_extract_tex_no(game, "NO", i);
		run_extract_tex_so(game, "SO", i);
		run_extract_tex_we(game, "WE", i);
		run_extract_tex_ea(game, "EA", i);
		run_extract_c(game, i);
		run_extract_f(game, i);
		i++;
	}
	check_tex_ext(game, ".xpm42");
	check_miss_tex(game);
	check_rgb(game);
	load_textures(game);
	return (NULL);
}
