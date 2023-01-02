/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:45:27 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/02 15:15:37 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

/* -Merging the old reads with the new ones
   -Resulting new string becomes unsorted */
char	*line_merge(char *new_line, char *unsorted_line)
{
	char					*new_string;
	unsigned int			i;

	i = 0;
	if (unsorted_line == NULL)
	{
		unsorted_line = malloc(sizeof(char) * 1);
		if (unsorted_line == NULL)
			return (NULL);
		*unsorted_line = '\0';
	}
	new_string = malloc(sizeof(char) * \
		(ft_strlen(new_line) + ft_strlen(unsorted_line) + 1));
	if (new_string == NULL)
		return (NULL);
	i = ft_strcpy(new_string, unsorted_line, 0);
	ft_strcpy(new_string + i, new_line, 0);
	ft_free(&unsorted_line);
	return (new_string);
}

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return (1);
	return (0);
}

void	ft_free(char **buf)
{
	free(*buf);
	*buf = NULL;
}

int	ft_strlen(const char *c)
{
	size_t				i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

int	ft_strcpy(char *dst, const char *src, size_t src_start)
{
	unsigned int				counter;

	counter = 0;
	while (src[src_start] != '\0')
	{
		dst[counter] = src[src_start];
		src_start++;
		counter++;
	}
	dst[counter] = '\0';
	return (counter);
}
