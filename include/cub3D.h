/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:44:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/09 13:01:00 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3D_H
# define cub3D_H

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

# define NAVY	0x0000FF55

# define GREEN	0x00FF00FF
//WINDOW SIZE
# define WIDTH		1080
# define HEIGHT		720
#define STEP 0.15


# define VALID_CHAR "10 NEWS-\n"
# define PLAYER_POS "NEWS"
# define MINIMAP_FACTOR	5
# define MINIMAP_SCOPE	10

int		args_check(t_game *data, int argc, char **argv);
int		init_all(t_game *game);
void	print_2d_array(char **array);
int		init_map(t_game *game);
char	*extract_tex(t_game *game);
int		map_isvalid(t_game *game);
int		check_valid_chars(char **map);

//Misc
void	error(char *str);
int		ft_line_count(char **array);
void	free_2d(char **matrix);
void	create_minimap(t_game *game);
void	update_minimap(t_game *game);

#endif 