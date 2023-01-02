/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:50:32 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/02 17:37:30 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


char *extract_tex_helper(char *str, char *tex_id)
{
	char *tex;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != tex_id[0] && str[i + 1] != tex_id[1])
		i++;
	i++;
	while (str[i] != '.')
		i++;
	tex = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (tex == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i] != ' ' &&  str[i] != '\0')
	{
		tex[j] = str[i];
		i++;
		j++;
	}
	tex[j] = '\0';
	return (tex);
}

char *extract_tex(t_game *game)
{
	int i;

	i = 1;

	while (i < 5)
	{
		if (ft_strnstr(game->map[0], "NO", 2) != NULL)
			game->tex->no = extract_tex_helper(game->map[i], "NO");
		else if (ft_strnstr(game->map[i], "SO", 2) != NULL)
			game->tex->so = extract_tex_helper(game->map[i], "SO");
		else if (ft_strnstr(game->map[i], "WE", 2) != NULL)
			game->tex->we = extract_tex_helper(game->map[i], "WE");
		else if (ft_strnstr(game->map[i], "EA", 2) != NULL)
			game->tex->ea = extract_tex_helper(game->map[i], "EA");
		i++;;
	}
	return (NULL);
}