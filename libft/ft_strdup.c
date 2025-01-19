/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:29:42 by juaho             #+#    #+#             */
/*   Updated: 2024/11/08 14:43:40 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	siz;

	siz = ft_strlen(s) + 1;
	ret = (char *) malloc(siz * sizeof(char));
	if (ret)
		ft_strlcpy(ret, s, siz);
	return (ret);
}
