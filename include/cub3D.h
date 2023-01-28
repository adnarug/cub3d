/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:44:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 14:23:48 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <memory.h>
# include <fcntl.h>
# include "structs.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include "math.h"
# define X	0
# define Y	1
# define I	0
# define J	1
# define NAVY			0x0000FFFF
# define BLACK			0x000000FF
# define GREEN			0x00FF00FF
# define NAVY			0x0000FFFF
# define RED			0xFF0000FF
# define GREEN_WALL		0x385b66FF
# define BACKG			0x8FC9AEFF
# define ROTATION_RADIANS 0.1
# define WIDTH			1080
# define HEIGHT			720
# define STEP			0.09
# define ROTATE_RIGHT	1
# define ROTATE_LEFT	-1
# define TEX_SCALE		64
# define VALID_CHAR		"10 NEWS-\n"
# define PLAYER_POS		"NEWS"
# define MINIMAP_SCALE	5
# define MINIMAP_SCOPE	10

int		args_check(int argc, char **argv);
int		init_map(t_game *game);
char	*extract_tex(t_game *game);
int		map_isvalid(t_game *game);
int		check_valid_chars(char **map);
void	rotate_vector(double v[2], double angle);
int		init_game(t_game *game);
void	init_mlx(t_game *game);
//Misc
int		free_game(t_game *game, bool img_flg);
int		ft_line_count(char **array);
void	free_2d(char **matrix);
void	update_minimap(t_game *game);
void	launch_minimap(t_game *game);
//RE
void	rays_minimap_line(t_game *game, double step);
void	move(t_game *game, double angle);
void	rotate_vector(double v[2], double angle);
void	rotate(t_game *data, int direction);
void	read_keys(mlx_key_data_t keycode, void *param);
void	extract_hex_color(t_game *game);
void	raycaster(t_game *game);
void	init_camera_plane(t_game *game);
int		convert_rgb_to_hex(int r, int g, int b);
void	texturize(t_game *game, int win_x, t_raycast *ray);
void	fill_ceiling(t_game *game);
void	fill_floor(t_game *game);
void	check_diag_holes(t_game *game);
int		perimeter_isvalid(t_game *game);
char	*extract_tex_helper(t_game *game, char *str_raw);
//Extraction of tex
void	run_extract_tex_no(t_game *game, char *str);
void	run_extract_tex_so(t_game *game, char *str);
void	run_extract_tex_ea(t_game *game, char *str);
void	run_extract_tex_we(t_game *game, char *str);
void	run_extract_c(t_game *game, char **str, char *one_str);
void	run_extract_f(t_game *game, char **str, char *one_str);
void	extract_hex_color(t_game *game);
void	extract_rgb_c(t_game *game);
void	extract_rgb_f(t_game *game);
char	*extract_tex(t_game *game);
void	access_tex(t_game *game);
void	check_tex_ext(t_game *game, char *ext);
void	check_miss_tex(t_game *game);
void	check_if_path(t_game *game, char *str_spl);
int		check_abbr(char *str);
void	extract_tex_rgb_helper(t_game *game, char **rgb, char *one_str);
char	**dup_matrix(t_game *game);
char	**read_map(t_game *game, char *file, int *line_count);
int		file_linecount(char *file);
int		find_player(t_game *game);
int		ft_ismapline(char *s);
char	**fill_spaces(t_game *game, char **map);
int		check_valid_chars(char **map);
int		find_map_start(char **map);
int		assign_player(t_game *game, int i, int j, int *one_pl_found);
void	init_player_angle(t_game *game);
void	rays_minimap_line(t_game *game, double step);
int		wrong_key_tex(t_game *game);
int		free_game_prs(t_game *game);
char	**init_rgb(t_game *game);
void	rgb_check(t_game *game);
void	check_rgb_null(t_game *game, char **rgb);
void	check_rgb_valid_char(t_game *game, char  *rgb);
void	check_commas(t_game *game, char **rgb);
int		check_extra_digits(t_game *game, char *str, int i);
int		iter_loop(char *str, int i);
//Err
int		error(char *str);
void	error_free_t_exit(t_game *game, char *str);
void	error_free_f_exit(t_game *game, char *str);
void	error_free_prs_exit(t_game *game, char *str);
#endif
