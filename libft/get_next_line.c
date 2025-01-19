/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:36:38 by juaho             #+#    #+#             */
/*   Updated: 2024/12/02 17:12:51 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static char	*append(char *str, char *buf);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*ret;
	int			read_ret;

	ret = NULL;
	while (1)
	{
		if (!buf[0])
		{
			read_ret = read(fd, buf, BUFFER_SIZE);
			if (read_ret < 0)
				break ;
			if (!buf[0])
				return (ret);
			buf[read_ret] = '\0';
		}
		ret = append(ret, buf);
		if (!ret)
			return (NULL);
		if (ret[ft_strlen(ret) - 1] == '\n')
			return (ret);
	}
	free(ret);
	return (NULL);
}

static	size_t	newline_index(char *buf)
{
	size_t	ret;

	ret = 0;
	while (ret < BUFFER_SIZE && buf[ret])
	{
		ret++;
		if (buf[ret - 1] == '\n')
			break ;
	}
	return (ret);
}

static char	*append(char *str, char *buf)
{
	char	*ret;
	size_t	str_len;
	size_t	buf_len;
	size_t	total_len;

	buf_len = newline_index(buf);
	str_len = 0;
	if (str)
		str_len = ft_strlen(str);
	total_len = str_len + buf_len;
	ret = (char *) malloc((total_len + 1) * sizeof(char));
	if (ret)
	{
		ft_memmove(ret, str, str_len);
		ft_memmove(ret + str_len, buf, buf_len);
		ft_bzero(buf, buf_len);
		ret[total_len] = '\0';
		ft_memmove(buf, buf + buf_len, BUFFER_SIZE - buf_len);
		ft_bzero(buf + BUFFER_SIZE - buf_len, buf_len);
	}
	free(str);
	return (ret);
}
