/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:46:48 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/27 17:57:38 by pguranda         ###   ########.fr       */
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
	write(2, str, ft_strlen(str));
	free_game(game, false);
	system("leaks cub3D");
	exit(1);
}

void	error_free_t_exit(t_game *game, char *str)
{
	write(2, str, ft_strlen(str));
	free_game(game, true);
	system("leaks cub3D");
	exit(1);
}

void	error_free_prs_exit(t_game *game, char *str)
{
	write(2, str, ft_strlen(str));
	free_game_prs(game);
	system("leaks cub3D");
	exit(1);
}
