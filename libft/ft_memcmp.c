/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:10:03 by juaho             #+#    #+#             */
/*   Updated: 2024/11/07 16:35:04 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	int				ret;

	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	ret = 0;
	while (n > 0)
	{
		ret = *p1 - *p2;
		if (ret)
			break ;
		p1++;
		p2++;
		n--;
	}
	return (ret);
}
