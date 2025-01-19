/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:25:15 by juaho             #+#    #+#             */
/*   Updated: 2024/11/21 13:40:37 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;
	size_t	offset;

	l_len = ft_strlen(little);
	offset = 0;
	if (l_len == 0)
		return ((char *) big);
	if (len)
	{
		while (l_len + offset <= len)
		{
			if (ft_strncmp(big + offset, little, l_len) == 0)
				return ((char *)big + offset);
			offset++;
		}
	}
	return (NULL);
}
