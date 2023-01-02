/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:44:52 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/02 17:04:17 by pguranda         ###   ########.fr       */
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
#define WIDTH 256
#define HEIGHT 256

int		args_check(t_game *data, int argc, char **argv);
int		init_all(t_game *game);
void	print_2d_array(char **array);
int		init_map(t_game *game);
char	*extract_tex(t_game *game);

//Misc
void	error(char *str);

#endif 