/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:27:15 by juaho             #+#    #+#             */
/*   Updated: 2024/11/13 10:18:29 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	tr_s;
	size_t	tr_e;

	if (!s1 || !set)
		return (NULL);
	tr_s = 0;
	tr_e = ft_strlen(s1) - 1;
	while (s1[tr_s] && is_in_set(s1[tr_s], set))
		tr_s++;
	if (tr_s < tr_e)
	{
		while (s1[tr_e] && is_in_set(s1[tr_e], set))
			tr_e--;
	}
	return (ft_substr(s1, tr_s, tr_e + 1 - tr_s));
}
