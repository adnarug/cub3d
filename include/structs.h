/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:05:10 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/11 09:05:52 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H


typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	double		x_scalar;
	double		y_scalar;
	double		camplane[2];
	t_vector	*direction;
	double		angle;
	double		angle_rad;
	char		dir;
}	t_player;

typedef struct s_map
{
	char	**map_raw;
	char	**map_clean;
	char	**map_filled;
	int		map_clean_lines;
	int		map_clean_start;
	char	*path;
	int		max_len;
}	t_map;

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

typedef struct s_mini
{
	mlx_image_t *img;
	int			size;
	int			x_offset;
	int			y_offset;
}	t_mini;

typedef struct s_game
{
	t_map		*map;
	t_textures	*tex;
	t_mini		*mini;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
}	t_game;

#endif
