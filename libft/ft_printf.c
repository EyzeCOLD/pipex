/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:12:20 by juaho             #+#    #+#             */
/*   Updated: 2024/11/21 10:38:29 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include "libft.h"
#include "ft_printf.h"

static int	print(int c, va_list ap);

static int	parse(const char *format, va_list ap);

static int	print_invalid(int c, int *invalid);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	if (!format)
		return (-1);
	va_start(ap, format);
	ret = parse(format, ap);
	va_end(ap);
	return (ret);
}

static int	print(int c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	else if (c == 'p')
		return (print_ptr(va_arg(ap, uintptr_t)));
	else if (c == 'd' || c == 'i')
		return (print_int(va_arg(ap, int), DECIMALS));
	else if (c == 'u')
		return (print_uint(va_arg(ap, unsigned int), DECIMALS));
	else if (c == 'x')
		return (print_uint(va_arg(ap, unsigned int), HEX_LOWER));
	else if (c == 'X')
		return (print_uint(va_arg(ap, unsigned int), HEX_UPPER));
	else if (c == '%')
		return (ft_putchar_fd('%', 1));
	return (-1);
}

static int	parse(const char *format, va_list ap)
{
	int	ret;
	int	write_ret;
	int	invalid;

	ret = 0;
	invalid = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (ft_memchr(FORMATS, *(format + 1), ft_strlen(FORMATS)))
				write_ret = print(*(++format), ap);
			else
				write_ret = print_invalid(*(++format), &invalid);
		}
		else
			write_ret = ft_putchar_fd(*format, 1);
		if (write_ret < 0)
			return (-1);
		ret += write_ret;
		if (*format)
			format++;
	}
	return (ret);
}

static int	print_invalid(int c, int *invalid)
{
	int	ret;

	ret = 0;
	if (c == '\0' && *invalid == 0)
		return (-1);
	if (ft_putchar_fd('%', 1) < 0)
		return (-1);
	*invalid = 1;
	if (c == '\0')
		return (1);
	ret = ft_putchar_fd(c, 1);
	if (ret < 0)
		return (-1);
	return (2);
}
