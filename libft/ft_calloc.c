/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:15:33 by juaho             #+#    #+#             */
/*   Updated: 2024/11/11 15:38:43 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	bytes;

	ptr = NULL;
	bytes = nmemb * size;
	if (bytes == 0 || bytes / nmemb == size)
		ptr = malloc(bytes);
	if (ptr)
		ft_memset(ptr, 0, bytes);
	return (ptr);
}
