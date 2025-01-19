/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:17:29 by juaho             #+#    #+#             */
/*   Updated: 2024/11/04 17:26:37 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		i;

	s = src;
	i = size;
	while (*s && i > 1)
	{
		*dst = *s;
		dst++;
		s++;
		i--;
	}
	if (size > 0)
		*dst = '\0';
	while (*s)
		s++;
	return (s - src);
}
