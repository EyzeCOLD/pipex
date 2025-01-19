/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:05:52 by juaho             #+#    #+#             */
/*   Updated: 2025/01/11 15:06:05 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

static size_t	count_elms(char	*cmd);
static int		populate_array(char	**arr, char *cmd);
void			free_arr(char ***arr);

/* Tokenizes a string, using space as the delimiter, but ignoring backspace
 * escaped spaces, so to allow parsing filenames with spaces in them
 */

char	**cmd_split(char *cmd)
{
	size_t	elms;
	char	**ret;

	elms = count_elms(cmd);
	if (elms == 0)
		return (NULL);
	ret = (char **) ft_calloc(sizeof(char *), elms + 1);
	if (!ret)
		return (NULL);
	if (populate_array(ret, cmd) == -1)
		free_arr(&ret);
	return (ret);
}

static size_t	count_elms(char	*cmd)
{
	size_t	elms;

	elms = 0;
	while (*cmd)
	{
		if (*cmd == ' ')
			while (*cmd == ' ')
				cmd++;
		else
		{
			elms++;
			while (*cmd && *cmd != ' ')
			{
				if (*cmd == '\\' && *(cmd + 1) == ' ')
					cmd++;
				cmd++;
			}
		}
	}
	return (elms);
}

static char	*substr_w_spaces(char *s, size_t len)
{
	size_t	escaped_spaces;
	size_t	i;
	char	*ret;

	i = 0;
	escaped_spaces = 0;
	while (i < len)
	{
		if (s[i] == '\\' && s[i + 1] == ' ')
			escaped_spaces++;
		i++;
	}
	ret = (char *) ft_calloc(sizeof(char), len - escaped_spaces + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len - escaped_spaces)
	{
		if (*s == '\\' && *(s + 1) == ' ')
			s++;
		ret[i] = *s;
		s++;
		i++;
	}
	return (ret);
}

static int	populate_array(char	**arr, char *cmd)
{
	char	*end;
	size_t	array_index;

	array_index = 0;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		end = cmd;
		while (*end && *end != ' ')
		{
			if (*end == '\\' && *(end + 1) == ' ')
				end++;
			end++;
		}
		arr[array_index] = substr_w_spaces(cmd, end - cmd);
		if (!arr[array_index])
			return (-1);
		cmd = end;
		array_index++;
	}
	return (0);
}

void	free_arr(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
