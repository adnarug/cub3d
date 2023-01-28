/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:44:29 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/28 13:02:38 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	args_num(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error\nWrong input - check the parameters\n", 41);
		return (EXIT_FAILURE);
	}
	if ((argv[1] == NULL || *argv[1] == '\0') && argc == 2)
	{
		write(2, "Error\nWrong input - check the parameters\n", 41);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_file_extension(char **argv)
{
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error\nWrong file extension - check the parameters\n", 50);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	args_check(int argc, char **argv)
{
	if (args_num(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_file_extension(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
