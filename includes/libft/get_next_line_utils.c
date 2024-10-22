/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:48:00 by amirfatt          #+#    #+#             */
/*   Updated: 2024/10/22 15:47:52 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_empty(char **stash)
{
	if (!*stash)
	{
		*stash = (char *)malloc(sizeof(char));
		if (!*stash)
			return ;
		(*stash)[0] = '\0';
	}
	if (!*stash)
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*ft_gnl_strjoin(char *stash, char *buff)
{
	char	*str_joined;
	size_t	i;
	size_t	j;

	handle_empty(&stash);
	if (!stash || !buff)
		return (NULL);
	str_joined = (char *)malloc(ft_strlen(buff) + ft_strlen(stash) + 2);
	if (!str_joined)
	{
		free(stash);
		return (NULL);
	}
	i = -1;
	j = 0;
	if (stash)
		while (stash[++i] != '\0')
			str_joined[i] = stash[i];
	while (buff[j] != '\0')
		str_joined[i++] = buff[j++];
	str_joined[ft_strlen(buff) + ft_strlen(stash)] = '\0';
	free(stash);
	return (str_joined);
}

int	check_len(char **new_stash)
{
	if (ft_strlen(*new_stash) == 0)
	{
		free(*new_stash);
		return (1);
	}
	return (0);
}

char	*read_into_new_stash(char *old_stash)
{
	char	*new_stash;
	int		i;
	int		j;

	if (!old_stash)
		return (NULL);
	i = 0;
	while (old_stash[i] && old_stash[i] != '\n')
		i++;
	i += (old_stash[i] == '\n');
	new_stash = (char *)malloc(ft_strlen(old_stash) - i + 1);
	if (!new_stash)
	{
		free(old_stash);
		return (NULL);
	}
	j = -1;
	while (old_stash[i + ++j])
		new_stash[j] = old_stash[i + j];
	new_stash[j] = '\0';
	free(old_stash);
	if (check_len(&new_stash))
		return (NULL);
	return (new_stash);
}
