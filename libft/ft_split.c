/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:09:09 by juaho             #+#    #+#             */
/*   Updated: 2024/11/14 12:19:14 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	int		in_word;

	words = 0;
	in_word = 0;
	while (*s)
	{
		if (*s++ == c)
		{
			if (in_word)
				in_word = 0;
		}
		else
		{
			if (!in_word)
			{
				in_word = 1;
				words++;
			}
		}
	}
	return (words);
}

static void	free_arr(char **arr, size_t elements)
{
	while (elements != 0)
	{
		free(arr[elements - 1]);
		elements--;
	}
	free(arr);
}

static void	split_words(char const *s, char c, size_t words, char **arr)
{
	char const	*ptr;
	size_t		arr_elm;

	arr_elm = 0;
	while (words-- > 0)
	{
		while (*s == c && *s)
			s++;
		ptr = s;
		while (*ptr != c && *ptr)
		{
			ptr++;
		}
		arr[arr_elm] = ft_substr(s, 0, ptr - s);
		if (arr[arr_elm] == NULL)
		{
			free_arr(arr, arr_elm + 1);
			return ;
		}
		s = ptr;
		arr_elm++;
	}
	arr[arr_elm] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **) malloc((words + 1) * sizeof(char *));
	if (arr != NULL)
		split_words(s, c, words, arr);
	return (arr);
}
