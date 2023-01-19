/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:01:15 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/19 12:22:46 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
int	ft_rgb_atoi(char *str)
{
	int		i;
	int		res;
	bool	str_invalid;


	if (str_invalid == true)
		return (-1);
	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	if (res < 0 || res > 255)
		return (-1);
	else
		return (res);
}

/*
	Separate colors and combine them back together with bit shifting method.
	The RGB parameter is always an int, represented as HEX Value.
*/
static int	convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

static int	extract_hex_color(t_game *data, char **rgb)
{
	int	color;

	get_rgb_values(data, rgb);
	if (data->tex->f->r == -1 || data->tex->f->g == -1 || data->tex->f->b == -1)
		color = -1;
	else
		color = convert_rgb_to_hex(data->tex->f->r, data->tex->f->g,
				data->tex->f->b);
	data->tex->f->r = -1;
	data->tex->f->g = -1;
	data->tex->f->b = -1;
	return (color);
}

void	draw_floor_ceiling(t_game *game)
{
	int x;
	int	y;
	int	fl;
	int	ce;
	
	y = 0;
	x = 0;
	ce = extract_hex_color(game, game->tex->c->rgb);
	printf (" ce %d\n", ce);
	fl = extract_hex_color(game, game->tex->c->rgb);
	printf (" fl %d\n", fl);
	while (y < HEIGHT / 2)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, extract_hex_color(game, game->tex->c->rgb));
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, extract_hex_color(game, game->tex->c->rgb));
			x++;
		}
		y++;
	}
}

/*ToDo: 
- the last char in the last row is substitued with '-'
- parsing of the textures without  "./" in the beginning
- getting close to the wall on top and left, bottom and right staying a step away*/
int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game);
	init_mlx(&game);
	if (args_check(&game, argc, argv) == EXIT_FAILURE)
		exit(1);
	init_map(&game);
	launch_minimap(&game);
	mlx_key_hook(game.mlx, &read_keys, (void *)&game);
	draw_floor_ceiling(&game);
	// launch(&game, argv);
	// mlx_hook(game.window, 2, 0, input, &game);
	// mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	// system("leaks cub3D");
	return (0);
}
