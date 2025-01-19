/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:47:05 by juaho             #+#    #+#             */
/*   Updated: 2024/11/11 17:27:34 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		substr_len;
	char		*substr;
	const char	*sub_start;

	if (!s)
		return (NULL);
	sub_start = s;
	while (*sub_start && start--)
		sub_start++;
	if (ft_strlen(sub_start) < len)
		substr_len = ft_strlen(sub_start);
	else
		substr_len = len;
	substr = (char *) malloc((substr_len + 1) * sizeof(char));
	if (substr)
		ft_strlcpy(substr, sub_start, substr_len + 1);
	return (substr);
}
