/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:50:32 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/19 15:10:28 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D.h"

static char	**extract_tex_rgb_helper(char *str, char *tex_id)
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
int	check_abbr(char *str)
{
	if ((ft_strncmp(str, "NO", 2) == 0) || (ft_strncmp(str, "SO", 2) == 0) || \
	(ft_strncmp(str, "EA", 2) == 0) ||(ft_strncmp(str, "WE", 2) == 0))
		return (0);
	else
		return (1);
}

/*-Space after NO*/
char *extract_tex_helper(t_game *game, char *str_raw)
{
	char	*tex;
	char	**str_spl;
	char	*start;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	str_spl = ft_split(str_raw, ' ');
	if (str_spl == NULL || *str_spl[0] == ' ')
	{
		error("Error\nTextures input is incorrect\n");
		exit (1);
	}
	if (check_abbr(str_spl[0]) != 0)
	{
		error("Error\nTextures input is incorrect\n");
		exit (1);
	}
	if (ft_strchr(str_spl[1], '/') == NULL)
	{
		error("Error\nTextures input is incorrect\n");
		exit (1);
	}
	game->tex->tex_spl = str_spl;
	print_2d_array(game->tex->tex_spl);
	start = str_spl[1];
	while (start[len] != '\0' && start[len] != ' ')
		len++;
	tex = malloc(sizeof(char) * (len + 1));
	if (tex == NULL)
		return (NULL);
	while (len > 0)
	{
		tex[j] = start[i];
		i++;
		j++;
		len--;
	}
	tex[j] = '\0';
	free_2d(str_spl);
	return (tex);
}

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

int	init_tex(t_game *game)
{
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
	return (EXIT_SUCCESS);
}

/*
	Separate colors and combine them back together with bit shifting method.
	The RGB parameter is always an int, represented as HEX Value.
*/
static int  convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void	extract_hex_color(t_game *game)
{
	game->tex->c->color = convert_rgb_to_hex(game->tex->c->r, game->tex->c->g, game->tex->c->b);
	game->tex->f->color = convert_rgb_to_hex(game->tex->f->r, game->tex->f->g, game->tex->f->b);
}


char *extract_tex(t_game *game)
{
	int		i;

	i = 0;
	// if (init_tex(game) == EXIT_FAILURE)
	// 	return (NULL);
	while (i < game->map->map_clean_start)
	{
		if ((ft_strnstr(game->map->map_raw[i], "NO ", ft_strlen(game->map->map_raw[i]))) != NULL)
			game->tex->no = extract_tex_helper(game, game->map->map_raw[i]);
		if (ft_strnstr(game->map->map_raw[i], "SO ", ft_strlen(game->map->map_raw[i])) != NULL)
			game->tex->so = extract_tex_helper(game, game->map->map_raw[i]);
		if (ft_strnstr(game->map->map_raw[i], "WE ", ft_strlen(game->map->map_raw[i])) != NULL)
			game->tex->we = extract_tex_helper(game, game->map->map_raw[i]);
		if (ft_strnstr(game->map->map_raw[i], "EA ", ft_strlen(game->map->map_raw[i])) != NULL)
			game->tex->ea = extract_tex_helper(game, game->map->map_raw[i]);
		if (ft_strnstr(game->map->map_raw[i], "F ", ft_strlen(game->map->map_raw[i])) != NULL)
		{
			game->tex->f->rgb = extract_tex_rgb_helper(game->map->map_raw[i], "F");
			extract_rgb(game, 'F');
		}
		if (ft_strnstr(game->map->map_raw[i], "C ",  ft_strlen(game->map->map_raw[i])) != NULL)
		{
			game->tex->c->rgb = extract_tex_rgb_helper(game->map->map_raw[i], "C");
			extract_rgb(game, 'C');
		}
		i++;
	}
	if (DEBUG == 1)
	{
		printf("\nno: %s\n", game->tex->no);
		printf("so: %s\n", game->tex->so);
		printf("we: %s\n", game->tex->we);
		printf("ea: %s\n", game->tex->ea);
		printf("f - r: %d\n", game->tex->f->r);
		printf("f - g: %d\n", game->tex->f->g);
		printf("f - b: %d\n", game->tex->f->b);
		printf("c - r: %d\n", game->tex->c->r);
		printf("c - g: %d\n", game->tex->c->g);
		printf("c - b: %d\n", game->tex->c->b);
	}
	return (NULL);
}