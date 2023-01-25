/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:46:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/25 13:45:41 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	error_free_f_exit(t_game *game, char *str)
{
	free_game(game, false);
	write(2, str, ft_strlen(str));
	exit(1);
}

void	error_free_t_exit(t_game *game, char *str)
{
	free_game(game, true);
	write(2, str, ft_strlen(str));
	exit(1);
}
