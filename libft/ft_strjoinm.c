/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:58:45 by juaho             #+#    #+#             */
/*   Updated: 2025/01/10 12:58:51 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

char	*ft_strjoinm(size_t	n, ...)
{
	va_list	strings;
	va_list	cpy;
	size_t	i;
	size_t	size;
	char	*ret;

	if (!n)
		return (NULL);
	va_start(strings, n);
	va_copy(cpy, strings);
	size = 1;
	i = 0;
	while (i++ < n)
		size += ft_strlen(va_arg(cpy, const char *));
	va_end(cpy);
	ret = (char *) ft_calloc(sizeof(char), size);
	if (ret)
	{
		i = 0;
		while (i++ < n)
			ft_strlcat(ret, va_arg(strings, char *), size);
	}
	va_end(strings);
	return (ret);
}
