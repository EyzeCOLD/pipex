/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:38:11 by juaho             #+#    #+#             */
/*   Updated: 2024/11/14 12:14:02 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *nptr)
{
	long	ret;
	int		ctoi;
	int		sign;

	ret = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		ctoi = sign * (*nptr - '0');
		if (sign == 1 && ret > (LONG_MAX - ctoi) / 10)
			return ((int) LONG_MAX);
		if (sign == -1 && ret < (LONG_MIN - ctoi) / 10)
			return ((int) LONG_MIN);
		ret = ret * 10 + ctoi;
		nptr++;
	}
	return (ret);
}
