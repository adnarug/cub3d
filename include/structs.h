/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:05:10 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/26 13:57:44 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	double		x_scalar;
	double		y_scalar;
	double		camplane[2];
	double		angle;

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
	int		r;
	int		g;
	int		b;
	char	**rgb;
	int		color;
}	t_tex_rgb;

typedef struct s_textures
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			**raw_path;
	bool			north_found;
	bool			south_found;
	bool			east_found;
	bool			west_found;
	bool			floor_found;
	bool			ceiling_found;
	xpm_t			*no;
	xpm_t			*so;
	xpm_t			*we;
	xpm_t			*ea;
	t_tex_rgb		*f;
	t_tex_rgb		*c;
}	t_textures;

typedef struct s_mini
{
	mlx_image_t	*img;
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

typedef struct s_raycast
{
	double	dir[2];
	double	ray_pos[2];
	double	delta_dist[2];
	double	side_dist[2];
	double	wall_dist;
	int		step[2];
	int		line_height;
	int		side;
}	t_raycast;

typedef struct s_ray_tex
{
	int		tex[2];
	double	step;
	double	pos;
	double	wall_x;
}	t_ray_tex;

#endif
