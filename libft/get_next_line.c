/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:38:32 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/29 22:03:56 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *buff, char *tmp)
{
	char	*temp;

	temp = ft_strjoin(buff, tmp);
	free(buff);
	return (temp);
}

char	*create_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line [i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*bin_line(char *buffer)
{
	char	*bin;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	bin = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!bin)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		bin[j++] = buffer[i++];
	free (buffer);
	return (bin);
}

char	*read_line(char *buffer, int fd)
{
	int		arch;
	char	*tmp;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	arch = 1;
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (arch > 0)
	{
		arch = read(fd, tmp, BUFFER_SIZE);
		if (arch == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp[arch] = 0;
		if (ft_strchr(tmp, '\0') != tmp + arch)
			return (NULL);
		buffer = ft_free(buffer, tmp);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
	{
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_line(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = create_line(buffer[fd]);
	buffer[fd] = bin_line(buffer[fd]);
	return (line);
}
