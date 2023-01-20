/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:44:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/20 16:57:55 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3D_H
# define cub3D_H

// MENU
#define VIS_RAYS 1 //turn on the cone of rays in Field of View in minimap, by default a line
#define DEBUG 0//if 1 debug mode for the map

# include "../lib/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "error.h"
# include "struct.h"
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include "structs.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include "math.h"

/* ************************************************************************** */
/* DEFINES                                                                    */
/* ************************************************************************** */

# define X	0
# define Y	1
# define I	0
# define J	1

# define NAVY	0x0000FFFF
# define BLACK  0x00000000
# define GREEN	0x00FF00FF
# define NAVY	0x0000FFFF
# define RED	   0xFF0000FF
#define GREEN_WALL 0x385b66FF
# define VAMP   0xc0C0C0FF
# define BACKG   0x8FC9AEFF
# define ROTATION_RADIANS 0.1
//WINDOW SIZE
# define WIDTH		1080
# define HEIGHT		720
#define  STEP        0.09
# define ROTATE_RIGHT 1
# define ROTATE_LEFT  -1
# define TEX_SCALE	64

# define VALID_CHAR "10 NEWS-\n"
# define PLAYER_POS "NEWS"
# define MINIMAP_SCALE	5
# define MINIMAP_SCOPE	10

int		args_check(t_game *data, int argc, char **argv);
int		init_all(t_game *game);
void	print_2d_array(char **array);
int		init_map(t_game *game);
char	*extract_tex(t_game *game);
int		map_isvalid(t_game *game);
int		check_valid_chars(char **map);
void	rotate_vector(double v[2], double angle);
int		init_game(t_game *game);
void    
init_mlx(t_game *game);
//Misc
void	error(char *str);
int		free_game(t_game *game);
int		ft_line_count(char **array);
void	free_2d(char **matrix);
void	create_minimap(t_game *game);
void	update_minimap(t_game *game);

//Minimap - BONUS
void	launch_minimap(t_game *game);
//RE
void	rays_minimap_cone(t_game *game, double step);
void	rays_minimap_line(t_game *game, double step);
void	move(t_game *game, double angle);
void	rotate_vector(double v[2], double angle);
void	rotate(t_game *data, int direction);
bool	check_collisions(t_game	*data, double new_v[2]);
void	read_keys(mlx_key_data_t keycode, void *param);
bool	check_collisions(t_game	*data, double new_v[2]);
void    extract_hex_color(t_game *game);
void	raycaster(t_game *game);
void	init_camera_plane(t_game *game);

int  convert_rgb_to_hex(int r, int g, int b);

#endif