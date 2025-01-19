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

static void	putnbr_recursion(long int n, int fd)
{
	char	c;

	c = n % 10 + '0';
	if (n / 10)
		putnbr_recursion(n / 10, fd);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = (long int) n * (-1);
	}
	else
		num = n;
	putnbr_recursion(num, fd);
}
