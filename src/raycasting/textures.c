/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:45 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/23 14:34:51 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	put_tex_pixel(t_game *game, int byte,
	mlx_texture_t *tex, int *screen)
{
	t_tex_rgb	tex_color;

	tex_color.r = tex->pixels[byte];
	tex_color.g = tex->pixels[byte + 1];
	tex_color.b = tex->pixels[byte + 2];
	tex_color.color = convert_rgb_to_hex(tex_color.r, tex_color.g, tex_color.b);
	mlx_put_pixel(game->img, screen[Y], screen[X], tex_color.color);
}

t_ray_tex	*calc_helper(t_game *game,
	t_raycast *ray, int *draw_start, int *draw_end)
{
	t_ray_tex	*tex;

	tex = malloc(sizeof(t_ray_tex));
	if (!tex)
		exit(1);
	*draw_start = (-ray->line_height / 2) + (HEIGHT / 2);
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (ray->line_height / 2) + (HEIGHT / 2);
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
	if (ray->side == 0)
		tex->wall_x = game->player->y_pos + ray->wall_dist * ray->dir[Y];
	else
		tex->wall_x = game->player->x_pos + ray->wall_dist * ray->dir[X];
	tex->wall_x -= floor((tex->wall_x));
	tex->tex[X] = (int)(tex->wall_x * (double)(TEX_SCALE));
	if (ray->side == 0 && ray->dir[X] > 0)
		tex->tex[X] = TEX_SCALE - tex->tex[X] - 1;
	if (ray->side == 1 && ray->dir[Y] < 0)
		tex->tex[X] = TEX_SCALE - tex->tex[X] - 1;
	tex->step = 1.0 * TEX_SCALE / ray->line_height;
	tex->pos = (*draw_start - HEIGHT / 2 + ray->line_height / 2) * tex->step;
	return (tex);
}

void	texturize(t_game *game, int win_x, t_raycast *ray)
{
	int			draw_start;
	int			draw_end;
	int			byte;
	int			screen[2];
	t_ray_tex	*tex;

	tex = calc_helper(game, ray, &draw_start, &draw_end);
	while (draw_start < draw_end)
	{
		tex->tex[Y] = (int)tex->pos & (TEX_SCALE - 1);
		tex->pos += tex->step;
		byte = (tex->tex[Y] * TEX_SCALE * 4) + (tex->tex[X] * 4);
		screen[X] = win_x;
		screen[Y] = draw_start;
		if (ray->side == 0 && ray->step[X] == 1)
			put_tex_pixel(game, byte, game->tex->ea, screen);
		else if (ray->side == 0)
			put_tex_pixel(game, byte, game->tex->we, screen);
		else if (ray->side == 1 && ray->step[Y] == -1)
			put_tex_pixel(game, byte, game->tex->so, screen);
		else
			put_tex_pixel(game, byte, game->tex->no, screen);
		draw_start++;
	}
	free(tex);
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
