/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:55:01 by amirfatt          #+#    #+#             */
/*   Updated: 2023/12/11 16:08:16 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line_before_n(char *stash)
{
	char	*string;
	int		checker;

	if (!stash || !stash[0])
		return (NULL);
	checker = 0;
	while (stash[checker] && stash[checker] != '\n')
	{
		checker++;
	}
	if (stash[checker] == '\n')
		checker++;
	string = (char *)malloc((1 + checker) * sizeof(char));
	if (!string)
		return (NULL);
	checker = 0;
	while (stash[checker] && stash[checker] != '\n')
	{
		string[checker] = stash[checker];
		checker++;
	}
	if (stash[checker] == '\n')
		string[checker++] = '\n';
	string[checker] = '\0';
	return (string);
}

void	handle_error(char **line, char **stash)
{
	free(*line);
	free(*stash);
	*stash = NULL;
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, line, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			handle_error(&line, &stash);
			return (NULL);
		}
		line[read_bytes] = '\0';
		stash = ft_gnl_strjoin(stash, line);
	}
	free(line);
	line = get_line_before_n(stash);
	stash = read_into_new_stash(stash);
	return (line);
}
