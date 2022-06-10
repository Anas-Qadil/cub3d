/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:20:42 by sakllam           #+#    #+#             */
/*   Updated: 2021/11/16 13:09:55 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(void **x)
{
	if (*x)
	{
		free(*x);
		*x = NULL;
	}
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		k;
	int		count;
	char	*p;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	count = i + k + 1;
	p = (char *) malloc(count * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	k = i;
	while (s1[k])
		p[i++] = s1[k++];
	k = 0;
	while (s2[k])
		p[i++] = s2[k++];
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i++;
	}
	if ((unsigned char) c == '\0' && s)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_onlyline(char *b, int *c)
{
	int		i;
	char	*p;

	i = 0;
	if (!b)
		return (NULL);
	while (b[i] != '\n' && b[i])
		i++;
	if (b[i] == '\n')
		i++;
	*c = i;
	p = (char *) malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < *c)
	{
		p[i] = b[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
