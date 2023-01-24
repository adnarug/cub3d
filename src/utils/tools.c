/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:03:21 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/24 15:07:21 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	ft_line_count(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}
