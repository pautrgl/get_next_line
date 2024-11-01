/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:41:32 by ptrapero          #+#    #+#             */
/*   Updated: 2024/10/28 17:45:46 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line_read;
	static char	*buffer;
	size_t	nbytes;
	ssize_t	hola;

	line
	hola = read(fd, buffer, BUFFER_SIZE);
	funcion read hasta encontrar salto linea (aqui strjoin)
	funcion poner hasta salto linea en line_read
	funcion resto buffer
	return (line_read);
	return (NULL);
}

int	main(void)
{
	int	fd;
	fd = open("prueba.txt", O_RDONLY);
	return (0);
}
