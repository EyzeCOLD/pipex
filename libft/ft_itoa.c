/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:02 by juaho             #+#    #+#             */
/*   Updated: 2024/11/13 10:30:43 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(int n)
{
	size_t	ret;

	ret = 0;
	while (n)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

static char	*return_zero(void)
{
	char	*ret;

	ret = (char *) malloc(2 * sizeof(char));
	if (ret)
	{
		ret[0] = '0';
		ret[1] = '\0';
	}
	return (ret);
}

static char	*itoa_from_positive(size_t n, size_t len)
{
	char	*ret;

	ret = (char *) malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (n)
	{
		ret[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	num;
	char	*a;

	if (n == 0)
		return (return_zero());
	len = num_len(n);
	num = n;
	if (n < 0)
	{
		num *= -1;
		len++;
	}
	a = itoa_from_positive((size_t) num, len);
	if (a && n < 0)
		*a = '-';
	return (a);
}
