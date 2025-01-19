/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:54:23 by juaho             #+#    #+#             */
/*   Updated: 2024/11/08 17:25:09 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ret;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	ret = ft_strlen(dst) + ft_strlen(src);
	while (*dst && i < size)
	{
		dst++;
		i++;
	}
	if (i >= size)
		return (size + ft_strlen(src));
	while (*src && i < size - 1)
	{
		*dst++ = *src++;
		i++;
	}
	if (dst)
		*dst = '\0';
	return (ret);
}
