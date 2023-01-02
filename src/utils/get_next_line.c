/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:45:34 by pguranda          #+#    #+#             */
/*   Updated: 2023/01/02 15:15:46 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

/*	- Read until the read \n or EOF, then put into unsorted line
	- Take out the next line from unsorted line
	- Take out the remainder from unsorted line
		put it at the start of unsorted for futer usage*/

char	*get_next_line(int fd)
{
	static char	*unsorted_line;
	char		*next_line;

	next_line = NULL;
	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	unsorted_line = read_until_nl(fd, unsorted_line);
	if (unsorted_line == NULL)
		return (NULL);
	if (*unsorted_line == '\0')
	{
		ft_free(&unsorted_line);
		return (NULL);
	}
	next_line = split_next_line(unsorted_line);
	unsorted_line = split_remainder(unsorted_line);
	return (next_line);
}

/*	- Repeated reads from fd until there is \n or EOF
	- Merge the old reads with the new reads */
char	*read_until_nl(int fd, char *unsorted_line)
{
	char	*new_line;
	int		read_result;

	read_result = 1;
	new_line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (new_line == NULL)
		return (NULL);
	while ((ft_strchr_gnl(unsorted_line, '\n') == 0) && read_result > 0)
	{
		read_result = read(fd, new_line, BUFFER_SIZE);
		if (read_result == -1)
		{
			free(new_line);
			new_line = NULL;
			return (NULL);
		}
		if (read_result == 0)
			break ;
		new_line[read_result] = '\0';
		unsorted_line = line_merge(new_line, unsorted_line);
	}
	free(new_line);
	new_line = NULL;
	return (unsorted_line);
}

/*	- Extract the new line from the unsorted
	- Malloc depending on whether it is the EOF */
char	*split_next_line(char *unsorted_line)
{
	char	*new_line;
	int		i;

	i = 0;
	while (unsorted_line[i] != '\n' && unsorted_line[i] != '\0')
		i++;
	if (unsorted_line[i] == '\n')
		new_line = malloc(sizeof(char) * (i + 2));
	else
		new_line = malloc(sizeof(char) * (i + 1));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (unsorted_line[i] != '\0' && unsorted_line[i] != '\n')
	{
		new_line[i] = unsorted_line[i];
		i++;
	}
	if (unsorted_line[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

/*	- Extract the remainder from the unsorted
	- Remainder becomes the new unsorted for future runs */
char	*split_remainder(char *unsorted_line)
{
	unsigned int		i;
	char				*remainder;

	i = 0;
	while (unsorted_line[i] != '\n' && unsorted_line[i] != '\0')
		i++;
	if (unsorted_line[i] == '\0')
	{
		ft_free(&unsorted_line);
		return (NULL);
	}
	remainder = malloc(sizeof(char) * (ft_strlen(unsorted_line) - i + 1));
	if (remainder == NULL)
		return (NULL);
	i++;
	ft_strcpy(remainder, unsorted_line, i);
	ft_free(&unsorted_line);
	return (remainder);
}
