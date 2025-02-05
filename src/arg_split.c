/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:26:10 by juaho             #+#    #+#             */
/*   Updated: 2025/02/05 16:12:07 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../inc/pipex.h"

static int	nothing_but_whitespace(char *arg);
static char	*format_arg(char *arg);
static char	*find_matching_quote(char *arg);

char	**arg_split(char *arg)
{
	char	*argf;
	char	**av;

	if (nothing_but_whitespace(arg))
	{
		av = ft_calloc(sizeof(char *), 2);
		if (!av)
			return (NULL);
		av[0] = ft_strdup(arg);
		av[1] = NULL;
		return (av);
	}
	argf = ft_strdup(arg);
	if (!argf)
		return (NULL);
	argf = format_arg(argf);
	av = ft_split(argf, -1);
	free(argf);
	return (av);
}

static int	nothing_but_whitespace(char *arg)
{
	while (*arg)
	{
		if (ft_isspace(*arg))
			return (1);
		arg++;
	}
	return (0);
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
			ft_memmove(&argf[i], &argf[i + 1], ft_strlen(&argf[i]));
			i += find_matching_quote(&argf[i]) - &argf[i];
			ft_memmove(&argf[i], &argf[i + 1], ft_strlen(&argf[i]));
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
		if (arg[i] == '\'')
			if (arg[i - 1] != '\\' || arg[i - 2] != '\\')
				return (&arg[i]);
		i++;
	}
	return (NULL);
}
