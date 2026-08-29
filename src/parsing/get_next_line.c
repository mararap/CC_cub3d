/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatanaso <jatanaso@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:09:23 by jatanaso          #+#    #+#             */
/*   Updated: 2025/05/28 14:32:31 by jatanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_until_newline(int fd, char *buffer)
{
	char	*temp_buf;
	ssize_t	bytes_read;
	char	*joined;

	temp_buf = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp_buf)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (free(temp_buf), NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(temp_buf), NULL);
		temp_buf[bytes_read] = '\0';
		joined = ft_strjoin(buffer, temp_buf);
		if (!joined)
			return (free(buffer), free(temp_buf), NULL);
		free(buffer);
		buffer = joined;
	}
	free(temp_buf);
	return (buffer);
}

static char	*substr_buffer(char *buffer)
{
	char	*new_line_char;
	char	*new_buf;
	size_t	end_idx;

	new_line_char = ft_strchr(buffer, '\n');
	if (!new_line_char)
		return (NULL);
	end_idx = (new_line_char - buffer) + 1;
	if (end_idx < ft_strlen(buffer))
	{
		new_buf = ft_substr(buffer, end_idx, ft_strlen(buffer) - end_idx);
		if (!new_buf)
			return (NULL);
		return (new_buf);
	}
	return (NULL);
}

static char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	char		*new_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	new_buffer = substr_buffer(buffer);
	free(buffer);
	buffer = new_buffer;
	return (line);
}
