/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:40:25 by juaho             #+#    #+#             */
/*   Updated: 2024/11/21 18:21:54 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"

static int	print_uint_recur(uintptr_t i, const char *base, size_t b_len)
{
	int	write_ret;
	int	ret;
	int	c;

	ret = 0;
	write_ret = 0;
	c = base[i % b_len];
	if (i / b_len)
	{
		ret = print_uint_recur(i / b_len, base, b_len);
		if (ret < 0)
			return (-1);
	}
	write_ret = ft_putchar_fd(c, 1);
	if (write_ret < 0)
		return (-1);
	return (ret++);
}

int	print_int(int i, const char *base)
{
	unsigned int	ui;
	int				sign;
	int				write_ret;

	sign = 0;
	if (i < 0)
	{
		ui = i * -1;
		if (ft_putchar_fd('-', 1) < 0)
			return (-1);
		sign++;
	}
	else
		ui = i;
	write_ret = print_uint_recur(ui, base, ft_strlen(base));
	if (write_ret < 0)
		return (-1);
	return (write_ret + sign);
}

int	print_uint(uintptr_t i, const char *base)
{
	return (print_uint_recur(i, base, ft_strlen(base)));
}

int	print_ptr(uintptr_t ptr)
{
	int	ret;

	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	if (ft_putstr_fd("0x", 1) < 0)
		return (-1);
	ret = print_uint(ptr, HEX_LOWER);
	if (ret < 0)
		return (-1);
	return (2 + ret);
}
