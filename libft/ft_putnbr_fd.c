/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:23:37 by juaho             #+#    #+#             */
/*   Updated: 2024/11/07 12:05:22 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	*str;
	int		ret;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	ret = ft_putstr_fd(str, fd);
	free(str);
	return (ret);
}
