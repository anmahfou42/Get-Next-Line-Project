/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmahfou <anmahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:27:02 by anmahfou          #+#    #+#             */
/*   Updated: 2024/12/17 13:06:42 by anmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_store(int fd, char *buffer)
{
	char	*buff_store;
	ssize_t	read_bytes;
	char	*temp;

	buff_store = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buff_store)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buff_store, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buff_store[read_bytes] = '\0';
		temp = ft_strjoin(buffer, buff_store);
		if (!temp)
		{
			free(buffer);
			free(buff_store);
			return (NULL);
		}
		free(buffer);
		buffer = temp;
	}
	free(buff_store);
	return (buffer);
}

char	*get_line(char *buffer)
{
	size_t	i;
	char	*line;

	if (!*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		i--;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_buffer(char *buffer)
{
	size_t	i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(&buffer[i + 1]);
	if (!new_buffer)
		return (NULL);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
int main ()
{



	
}