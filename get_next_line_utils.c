/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptrapero <ptrapero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:46:23 by ptrapero          #+#    #+#             */
/*   Updated: 2024/10/28 17:48:57 by ptrapero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup (""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	i = 0;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (len > i)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*conc;

	i = 0;
	j = 0;
	conc = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (conc == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		conc[j] = s1[j];
		j++;
	}
	while (s2[i] != '\0')
	{
		conc[j] = s2[i];
		i++;
		j++;
	}
	conc[j] = '\0';
	return (conc);
}

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*t;

	t = (unsigned char *)s;
	while (n > 0)
	{
		*t = 0;
		t++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	mem = malloc(sizeof(char) * size * nmemb);
	if (mem == NULL)
		return (NULL);
	mem = ft_bzero(mem, size * nmemb);
	return (mem);
}
