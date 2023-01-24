/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:50:32 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 14:37:35 by jtsizik          ###   ########.fr       */
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
char *extract_tex_helper(char *str_raw)
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
		return (NULL);
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
	start = str_spl[1];
	while (start[len] != '\0' && start[len] != ' ')
	len++;
	tex = malloc(sizeof(char) * (len + 1));
	if (tex == NULL)
		return (NULL);
	len--;
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
	game->tex->no_path = NULL;
	game->tex->so_path = NULL;
	game->tex->ea_path = NULL;
	game->tex->we_path = NULL;
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
int  convert_rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}
void    extract_hex_color(t_game *game)
{
	game->tex->c->color = convert_rgb_to_hex(game->tex->c->r, game->tex->c->g, game->tex->c->b);
	game->tex->f->color = convert_rgb_to_hex(game->tex->f->r, game->tex->f->g, game->tex->f->b);
}

void	load_textures(t_game *game)
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

void	check_miss_tex(t_game *game)
{
	if (game->tex->ceiling_found == false || game->tex->floor_found == false)
		exit(error("Error\nSome texture(s) missing\n"));
	if (game->tex->north_found == false || game->tex->south_found == false || \
		game->tex->south_found == false || game->tex->west_found == false)
		exit(error("Error\nSome texture(s) missing\n"));

}

void	check_tex_ext(t_game *game, char *ext)
{
	int	len;

	len = ft_strlen(ext);
	if (ft_strncmp(game->tex->no_path + ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
	if (ft_strncmp(game->tex->so_path + ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
	if (ft_strncmp(game->tex->we_path + ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
	if (ft_strncmp(game->tex->ea_path + ft_strlen(game->tex->no_path) - len, ext, len) != 0)
		exit(error("Error\nWrong texture extension\n"));
}
void	access_tex(t_game *game)
{
	if (access(game->tex->no_path, F_OK ) == -1)
		exit(error("Error\nCould not access texture file(s)N\n"));
	if (access(game->tex->so_path, F_OK ) == -1)
		exit(error("Error\nCould not access texture file(s)S\n"));
	if (access(game->tex->we_path, F_OK) == -1)
		exit(error("Error\nCould not access texture file(s)W \n"));
	if (access(game->tex->ea_path, F_OK) == -1)
		exit(error("Error\nCould not access texture file(s)E\n"));
}
char *extract_tex(t_game *game)
{
	int		i;

	i = 0;
	// access_tex(game);
	// if (init_tex(game) == EXIT_FAILURE)
	// 	return (NULL);
	while (i < game->map->map_clean_start)
	{
		if ((ft_strnstr(game->map->map_raw[i], "NO ", ft_strlen(game->map->map_raw[i]))) != NULL)
		{
			if (game->tex->north_found == true)
				exit (error("Error\nDuplicate textures input\n"));
			game->tex->no_path = extract_tex_helper(game->map->map_raw[i]);
			if (access(game->tex->no_path, F_OK | R_OK ) == -1)
				exit(error("Error\nCould not access texture file(s)N\n"));
			if (game->tex->no_path != NULL)
				game->tex->north_found = true;
		}
		if (ft_strnstr(game->map->map_raw[i], "SO ", ft_strlen(game->map->map_raw[i])) != NULL)
		{
			if (game->tex->south_found == true)
				exit (error("Error\nDuplicate textures input\n"));
			game->tex->so_path = extract_tex_helper(game->map->map_raw[i]);
			if (access(game->tex->so_path, F_OK | R_OK ) == -1)
				exit(error("Error\nCould not access texture file(s)S\n"));
			if (game->tex->so_path != NULL)
				game->tex->south_found = true;
		}
		if (ft_strnstr(game->map->map_raw[i], "WE ", ft_strlen(game->map->map_raw[i])) != NULL)
		{
			if (game->tex->west_found == true)
				exit (error("Error\nDuplicate textures input\n"));
			game->tex->we_path = extract_tex_helper(game->map->map_raw[i]);
			if (access(game->tex->we_path, F_OK | R_OK) == -1)
				exit(error("Error\nCould not access texture file(s)W\n"));
			if (game->tex->we_path != NULL)
				game->tex->west_found = true;
		}
		if (ft_strnstr(game->map->map_raw[i], "EA ", ft_strlen(game->map->map_raw[i])) != NULL)
		{
			if (game->tex->east_found == true)
				exit (error("Error\nDuplicate textures input\n"));
			game->tex->ea_path = extract_tex_helper(game->map->map_raw[i]);
			if (access(game->tex->ea_path, F_OK | R_OK) == -1)
				exit(error("Error\nCould not access texture file(s)E\n"));
			if (game->tex->ea_path != NULL)
				game->tex->east_found = true;
		}
		if (ft_strnstr(game->map->map_raw[i], "F ", ft_strlen(game->map->map_raw[i])) != NULL)
		{
			if (game->tex->floor_found == true)
				exit (error("Error\nDuplicate textures input\n"));
			game->tex->f->rgb = extract_tex_rgb_helper(game->map->map_raw[i], "F");
			extract_rgb(game, 'F');
			if (game->tex->f->rgb!= NULL)
				game->tex->floor_found = true;
		}
		if (ft_strnstr(game->map->map_raw[i], "C ",  ft_strlen(game->map->map_raw[i])) != NULL)
		{
			if (game->tex->ceiling_found == true)
				exit (error("Error\nDuplicate textures input\n"));
			game->tex->c->rgb = extract_tex_rgb_helper(game->map->map_raw[i], "C");
			extract_rgb(game, 'C');
			if (game->tex->c->rgb != NULL)
				game->tex->ceiling_found = true;
		}
		i++;
	}
	check_tex_ext(game, ".xpm42");
	check_miss_tex(game);
	if (DEBUG == 1)
	{
		printf("\nno: %s\n", game->tex->no_path);
		printf("so: %s\n", game->tex->so_path);
		printf("we: %s\n", game->tex->we_path);
		printf("ea: %s\n", game->tex->ea_path);
		printf("f - r: %d\n", game->tex->f->r);
		printf("f - g: %d\n", game->tex->f->g);
		printf("f - b: %d\n", game->tex->f->b);
		printf("c - r: %d\n", game->tex->c->r);
		printf("c - g: %d\n", game->tex->c->g);
		printf("c - b: %d\n", game->tex->c->b);
	}
	load_textures(game);
	return (NULL);
}