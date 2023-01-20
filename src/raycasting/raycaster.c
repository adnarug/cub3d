/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:16:23 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/20 18:14:55 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	cast_ray(t_game *game, double dir_x, double dir_y, int win_x)
{
	double	pos[2];
	double	ray[2];
	int		step[2];
	double	deltaDist[2];
	double	map_pos[2];
	double	sideDist[2];
	double	wallDist;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	pos[X] = game->player->x_pos;
	pos[Y] = game->player->y_pos;
	deltaDist[X] = fabs(1 / dir_x);
	deltaDist[Y] = fabs(1 / dir_y);
	map_pos[X] = (int)pos[X];
	map_pos[Y] = (int)pos[Y];
	ray[X] = (double)map_pos[X];
	ray[Y] = (double)map_pos[Y];
	if (dir_x < 0)
	{
		step[X] = -1;
		sideDist[X] = (pos[X] - map_pos[X]) * deltaDist[X];
	}
	else
    {
		step[X] = 1;
		sideDist[X] = (map_pos[X] + 1.0 - pos[X]) * deltaDist[X];
    }
	if (dir_y < 0)
	{
		step[Y] = -1;
		sideDist[Y] = (pos[Y] - map_pos[Y]) * deltaDist[Y];
	}
	else
    {
		step[Y] = 1;
		sideDist[Y] = (map_pos[Y] + 1.0 - pos[Y]) * deltaDist[Y];
    }
	while (1)
	{
		if (sideDist[X]< sideDist[Y])
        {
        	sideDist[X] += deltaDist[X];
        	ray[X] += step[X];
			side = 0;
        }
		else
        {
        	sideDist[Y] += deltaDist[Y];
        	ray[Y] += step[Y];
			side = 1;
		}
		if (game->map->map_filled[(int)ray[X]][(int)ray[Y]] == '1')
 				break ;
	}
	if (side == 0)
		wallDist = sideDist[X] - deltaDist[X];
	else
		wallDist = sideDist[Y] - deltaDist[Y];

	lineHeight = (int)(HEIGHT / wallDist);

    drawStart = (-lineHeight / 2) + (HEIGHT / 2);
    if (drawStart < 0)
		drawStart = 0;
    drawEnd = (lineHeight / 2) + (HEIGHT / 2);
    if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;

	//TEXTURISING
	double	wallX;
    if (side == 0)
		wallX = game->player->y_pos + wallDist * dir_y;
    else
		wallX = game->player->x_pos + wallDist * dir_x;
    wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(TEX_SCALE));
    if (side == 0 && dir_x > 0)
		texX = TEX_SCALE - texX - 1;
    if (side == 1 && dir_y < 0)
		texX = TEX_SCALE - texX - 1;
	double tex_step = 1.0 * TEX_SCALE / lineHeight;
	double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * tex_step;
	while (drawStart < drawEnd)
	{
		int texY = (int)texPos & (TEX_SCALE - 1);
		texPos += tex_step;
		int byte = (texY * TEX_SCALE * 4) + (texX * 4);
		if (side == 0)
		{
			int r = game->tex->no_tex->pixels[byte];
			int g = game->tex->no_tex->pixels[byte + 1];
			int b = game->tex->no_tex->pixels[byte + 2];
			int tex_color = convert_rgb_to_hex(r, g, b);
			mlx_put_pixel(game->img, win_x, drawStart, tex_color);
		}
		else
		{
			int r = game->tex->ea_tex->pixels[byte];
			int g = game->tex->ea_tex->pixels[byte + 1];
			int b = game->tex->ea_tex->pixels[byte + 2];
			int tex_color = convert_rgb_to_hex(r, g, b);
			mlx_put_pixel(game->img, win_x, drawStart, tex_color);
		}
		drawStart++;
	}
}

void	fill_ceiling(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT / 2)
		{
			mlx_put_pixel(game->img, x, y, game->tex->c->color);
			y++;
		}
		y = 0;
		x++;
	}
}

void	fill_floor(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = HEIGHT / 2;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->img, x, y, game->tex->f->color);
			y++;
		}
		y = HEIGHT / 2;
		x++;
	}
}

void	load_texture(t_game *game)
{
	xpm_t	*xpm;
	xpm_t	*xpm2;

	xpm = mlx_load_xpm42("assets/NO.xpm42");
	game->tex->no_tex = &xpm->texture;
	xpm2 = mlx_load_xpm42("assets/EA.xpm42");
	game->tex->ea_tex = &xpm2->texture;
}

void	raycaster(t_game *game)
{
	double	camera[2];
	int		win_x;

	win_x = 0;
	load_texture(game);
	extract_hex_color(game);
	fill_ceiling(game);
	fill_floor(game);
	while (win_x < WIDTH)
	{
		camera[X] = 2 * win_x / (double)WIDTH - 1;
      	double rayDirX = game->player->x_scalar + game->player->camplane[X] * camera[X];
      	double rayDirY = game->player->y_scalar + game->player->camplane[Y] * camera[X];
		cast_ray(game, rayDirX, rayDirY, win_x);
		win_x++;
	}
}
