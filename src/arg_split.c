/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:26:10 by juaho             #+#    #+#             */
/*   Updated: 2025/01/30 23:00:33 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../inc/pipex.h"

static char	*format_arg(char *arg);
static char	*find_matching_quote(char *arg);

char	**arg_split(char *arg)
{
	char	*argf;
	char	**av;

	if (ft_strlen(arg) == 1)
		return (ft_split(arg, -1));
	argf = ft_strdup(arg);
	if (!argf)
		return (NULL);
	argf = format_arg(argf);
	av = ft_split(argf, -1);
	free(argf);
	return (av);
}

static char	*format_arg(char *argf)
{
	const char	*escapeable;
	size_t		i;

	escapeable = "\\ \'";
	i = 0;
	while (argf[i])
	{
		if (argf[i] == '\\' && ft_strchr(escapeable, argf[i + 1]))
			ft_memmove(&argf[i], &argf[i + 1], ft_strlen(&argf[i]));
		else if (argf[i] == '\'' && find_matching_quote(&argf[i]))
		{
			argf[i] = -1;
			i += find_matching_quote(&argf[i]) - &argf[i];
			argf[i] = -1;
		}
		else if (argf[i] == ' ')
			argf[i] = -1;
		i++;
	}
	return (argf);
}

static char	*find_matching_quote(char *arg)
{
	size_t	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == '\'' && (i == 1 || arg[i - 1] != '\\'))
			return (&arg[i]);
		i++;
	}
	return (NULL);
}
