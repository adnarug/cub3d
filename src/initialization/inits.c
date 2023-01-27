/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:46:07 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/27 18:02:10 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_tex(t_game *game)
{
	game->tex->no_path = NULL;
	game->tex->so_path = NULL;
	game->tex->ea_path = NULL;
	game->tex->we_path = NULL;
	game->tex->north_found = false;
	game->tex->south_found = false;
	game->tex->east_found = false;
	game->tex->west_found = false;
	game->tex->floor_found = false;
	game->tex->ceiling_found = false;
}

int	init_game(t_game *game)
{
	game->tex = malloc(sizeof(t_textures));
	if (game->tex == NULL)
		return (EXIT_FAILURE);
	game->map = malloc(sizeof(t_map));
	if (game->map == NULL)
		return (EXIT_FAILURE);
	game->tex->f = malloc(sizeof(t_tex_rgb));
	if (game->tex->f == NULL)
		return (EXIT_FAILURE);
	game->tex->c = malloc(sizeof(t_tex_rgb));
	if (game->tex->c == NULL)
		return (EXIT_FAILURE);
	game->player = malloc(sizeof(t_player));
	if (game->player == NULL)
		return (EXIT_FAILURE);
	init_tex(game);
	return (EXIT_SUCCESS);
}

void	init_mlx(t_game *game)
{
	mlx_t			mlx;
	mlx_image_t		img;

	game->mlx = &mlx;
	game->img = &img;
	mlx_set_setting(MLX_MAXIMIZED, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (game->mlx == NULL)
		exit(1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	init_camera_plane(t_game *game)
{
	game->player->camplane[X] = 0.5 * game->player->x_scalar;
	game->player->camplane[Y] = 0.5 * game->player->y_scalar;
	rotate_vector(game->player->camplane, 0.5 * M_PI);
}
