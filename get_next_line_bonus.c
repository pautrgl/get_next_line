/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:41:32 by ptrapero          #+#    #+#             */
/*   Updated: 2024/11/11 21:58:40 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_delete_line(char *buffer)
{
	int		i;
	char	*update_buffer;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	update_buffer = ft_substr(buffer, i, (ft_strlen(buffer) - i));
	if (!update_buffer)
		return (NULL);
	free(buffer);
	return (update_buffer);
}

static char	*ft_return_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*ft_buff_read(int fd, char *buffer)
{
	int		cont;
	char	*temp_buff;

	temp_buff = malloc(BUFFER_SIZE + 1);
	if (!temp_buff)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	cont = 1;
	while (!ft_strchr(buffer, '\n') && cont > 0)
	{
		cont = read(fd, temp_buff, BUFFER_SIZE);
		if (cont == -1)
			return (free(buffer), free(temp_buff), NULL);
		temp_buff[cont] = '\0';
		buffer = ft_strjoin_free(buffer, temp_buff);
	}
	return (free(temp_buff), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[NUM_FD];
	char		*line_read;

	if (fd < 0 || fd >= NUM_FD || BUFFER_SIZE < 1)
		return (NULL);
	buffer[fd] = ft_buff_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line_read = ft_return_line(buffer[fd]);
	if (line_read[0] == '\0')
	{
		free(buffer[fd]);
		free(line_read);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_delete_line(buffer[fd]);
	return (line_read);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*text;

// 	fd = open("prueba.txt", O_RDONLY);
// 	text = get_next_line(fd);
// 	while (text)
// 	{
// 		printf("%s", text);
// 		free(text);
// 		text = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("patatasfritas.txt", O_RDONLY);
// 	text = get_next_line(fd);
// 	while (text)
// 	{
// 		printf("%s", text);
// 		free(text);
// 		text = get_next_line(fd);
// 	}
// 	close(fd);
// 	return(0);
// }
