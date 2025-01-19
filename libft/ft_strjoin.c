/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:12:58 by juaho             #+#    #+#             */
/*   Updated: 2024/11/11 16:32:35 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *) malloc((len + 1) * sizeof(char));
	if (ret)
	{
		*ret = '\0';
		ft_strlcat(ret, s1, len + 1);
		ft_strlcat(ret, s2, len + 1);
	}
	return (ret);
}
