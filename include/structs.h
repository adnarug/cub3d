/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:05:10 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/04 16:41:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_tex_rgb
{
	int			r;
	int			g;
	int			b;
	char	**rgb;
}	t_tex_rgb;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	t_tex_rgb		*f;
	t_tex_rgb		*c;
}	t_textures;

typedef struct s_game
{
	char		*map_path;
	char		**map;
	char		**only_map;
	int			only_map_lines;
	t_textures	*tex;
}	t_game;

#endif
