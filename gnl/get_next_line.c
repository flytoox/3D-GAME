/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:46:33 by obelaizi          #+#    #+#             */
/*   Updated: 2023/09/26 22:27:02 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size;
	int		i;
	int		j;
	int		check;

	if (!(*s2))
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	i = -1;
	j = 0;
	check = ft_len(s1);
	size = check + ft_len(s2);
	result = malloc(size + 1);
	if (!result)
		return (0);
	while (++i < check)
		result[i] = s1[i];
	while (i < size)
		result[i++] = s2[j++];
	return (free(s1), result[i] = 0, result);
}

char	*ignore(char *s)
{
	int		i;
	char	*result;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	result = ft_strjoin(NULL, &s[i]);
	return (free(s), result);
}

char	*fill(char *src)
{
	int		i;
	char	*dst;
	int		j;

	j = 0;
	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (free(src), NULL);
	if (src[i - 1] == '\n')
		i--;
	dst[i] = 0;
	while (i--)
		dst[j++] = *(src++);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buf;
	char		*result;
	int			i;

	if (handle_error(rest, fd))
		return (rest = NULL, NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!check_char(rest, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = 0;
		if (!i)
			break ;
		rest = ft_strjoin(rest, buf);
	}
	if (!rest)
		return (free(buf), NULL);
	if (!(*rest))
		return (free(rest), free(buf), NULL);
	return (result = fill(rest), free(buf), rest = ignore(rest), result);
}
