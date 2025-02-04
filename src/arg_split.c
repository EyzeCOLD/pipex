/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:26:10 by juaho             #+#    #+#             */
/*   Updated: 2025/02/04 18:13:53 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../inc/pipex.h"

static int	whitespace_arg(char *arg);
static char	*format_arg(char *arg);
static char	*find_matching_quote(char *arg);

char	**arg_split(char *arg)
{
	char	*argf;
	char	**av;

	if (whitespace_arg(arg))
	{
		av = (char **) ft_calloc(sizeof(char *), 2);
		if (!av)
			return (NULL);
		av[0] = ft_strdup(arg);
		if (!av[0])
		{
			free_av(&av);
			return (NULL);
		}
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

static int	whitespace_arg(char *arg)
{
	while (*arg)
	{
		if (!ft_isspace(*arg))
			return (0);
		arg++;
	}
	return (1);
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
			i += find_matching_quote(&argf[i]) - &argf[i];
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
