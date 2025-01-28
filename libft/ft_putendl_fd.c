/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:21:53 by juaho             #+#    #+#             */
/*   Updated: 2024/11/21 10:27:23 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	char	*str;
	int		ret;

	str = ft_strjoin(s, "\n");
	if (!str)
		return (-1);
	ret = ft_putstr_fd(str, fd);
	free(str);
	return (ret);
}
