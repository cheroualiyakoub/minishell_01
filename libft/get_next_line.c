/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:35:06 by ashirzad          #+#    #+#             */
/*   Updated: 2024/04/23 19:24:04 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_static_buffer(char **list)
{
	if ((*list) != NULL)
	{
		free(*list);
		*list = NULL;
	}
}

static char	*polish_list(char **list)
{
	char	*buffer;
	int		i;

	i = 0;
	if (list == NULL)
		return (NULL);
	while ((*list)[i] && (*list)[i] != '\n')
		i++;
	if ((*list)[i] == '\0' || (*list)[i + 1] == '\0')
		return (NULL);
	i += 1;
	buffer = ft_strdup((*list) + i);
	if (buffer == NULL)
	{
		free_static_buffer(list);
		return (NULL);
	}
	return (buffer);
}

static char	*polish_line(char **list)
{
	char	*temp;
	char	*str;
	int		i;

	i = 0;
	if (!(*list) || !(*list)[0])
		return (NULL);
	while ((*list)[i] && (*list)[i] != '\n')
		i++;
	str = (char *)malloc((i + 1) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while ((*list)[++i] && ((*list)[i] != '\n' && (*list)[i + 1] != '\0'))
		str[i] = (*list)[i];
	if ((*list)[i] == '\n' || (*list)[i + 1] == '\0')
	{
		str[i] = (*list)[i];
		str[i + 1] = '\0';
		temp = polish_list(list);
		free_static_buffer(list);
		*list = temp;
		return (str);
	}
	return (NULL);
}

static void	create_line(char **list, int fd)
{
	char		*buffer;
	int			chars_read;
	char		*temp;

	chars_read = 0;
	while (*list == NULL || ft_strchr(*list, '\n') == NULL)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		chars_read = (int)read(fd, buffer, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[chars_read] = '\0';
		temp = *list;
		*list = ft_strjoin(*list, buffer);
		free(temp);
		free(buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*list;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free_static_buffer(&list);
		return (NULL);
	}
	create_line(&list, fd);
	if (list == NULL)
		return (NULL);
	line = polish_line(&list);
	return (line);
}
