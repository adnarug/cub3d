/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:05:45 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 17:16:14 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_abbr(char *str)
{
	if ((ft_strncmp(str, "NO", 2) == 0) || (ft_strncmp(str, "SO", 2) == 0) || \
		(ft_strncmp(str, "EA", 2) == 0) || (ft_strncmp(str, "WE", 2) == 0))
		return (0);
	else
		return (1);
}

static void	check_if_path(t_game *game, char **str_spl)
{
	if (check_abbr(str_spl[0]) != 0 || \
	(ft_strchr(str_spl[1], '/') == NULL))
	{
		free_game(game, false);
		exit(error("Error\nTextures input is incorrect\n"));
	}
}

char	*extract_tex_helper(t_game *game, char *str_raw)
{
	char	*tex;
	char	**str_spl;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	str_spl = ft_split(str_raw, ' ');
	if (str_spl == NULL || *str_spl[0] == ' ')
		return (NULL);
	check_if_path(game, str_spl);
	while (str_spl[1][len] != '\0' && str_spl[1][len] != ' ')
		len++;
	tex = malloc(sizeof(char) * (len + 1));
	if (tex == NULL)
		return (NULL);
	while (--len > 0)
		tex[j++] = str_spl[1][i++];
	tex[j] = '\0';
	free_2d(str_spl);
	return (tex);
}