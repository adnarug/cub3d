/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:50:32 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/06 17:17:40 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define DEBUG 0
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

/*-Space after NO*/
char *extract_tex_helper(char *str, char *tex_id)
{
	char *tex;
	char *start;
	int	len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = 0;
	str = ft_strnstr(str, tex_id, ft_strlen(str));
	if (str == NULL)
		return (NULL);
	start = ft_strnstr(str, "./", ft_strlen(str));
	if (start == NULL)
		return (NULL);
	while (start[len] != '\0' && start[len] != ' ')
		len++;
	tex = malloc(sizeof(char) * (len));
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

char *extract_tex(t_game *game)
{
	int		i;

	i = 0;
	// if (init_tex(game) == EXIT_FAILURE)
	// 	return (NULL);
	while (i < game->map->map_clean_start)
	{
		if ((ft_strnstr(game->map->map_raw[i], "NO ", ft_strlen(game->map->map_raw[i]))) != NULL)
			game->tex->no = extract_tex_helper(game->map->map_raw[i], "NO");
		if (ft_strnstr(game->map->map_raw[i], "SO ", ft_strlen(game->map->map_raw[i])) != NULL)
			game->tex->so = extract_tex_helper(game->map->map_raw[i], "SO");
		if (ft_strnstr(game->map->map_raw[i], "WE ", ft_strlen(game->map->map_raw[i])) != NULL)
			game->tex->we = extract_tex_helper(game->map->map_raw[i], "WE");
		if (ft_strnstr(game->map->map_raw[i], "EA ", ft_strlen(game->map->map_raw[i])) != NULL)
			game->tex->ea = extract_tex_helper(game->map->map_raw[i], "EA");
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