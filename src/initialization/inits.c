/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:46:07 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/11 16:52:44 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int		init_game(t_game *game)
{
	game->tex = malloc(sizeof(t_textures));
	if (game->tex == NULL)
		return (EXIT_FAILURE);
	game->map = malloc(sizeof(t_map));
	if (game->map == NULL)
		return (EXIT_FAILURE);
	game->tex->no = NULL;
	game->tex->so = NULL;
	game->tex->ea = NULL;
	game->tex->we = NULL;
	game->tex->f = malloc(sizeof(t_tex_rgb));
	if (game->tex->f == NULL)
		return (EXIT_FAILURE);
	game->tex->c = malloc(sizeof(t_tex_rgb));
	if (game->tex->c == NULL)
		return (EXIT_FAILURE);
	game->player = malloc(sizeof(t_player));
	if (game->player == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void init_mlx(t_game *game)
{
	mlx_t			mlx;
	mlx_image_t		img;

	game->mlx = &mlx;
	game->img = &img;
	mlx_set_setting(MLX_MAXIMIZED, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (game->mlx == NULL)
		exit(1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	init_camera_plane(t_game *data)
{
	data->player->camplane[X] = 0.5 * data->player->x_scalar;
	data->player->camplane[Y] = 0.5 * data->player->y_scalar;
	rotate_vector(data->player->camplane, 0.5 * M_PI);
}