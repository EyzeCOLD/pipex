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
static void	erase_char(char *s);

char	**arg_split(char *arg)
{
	char	*arg_formatted;
	char	**av;

	if (!*arg || nothing_but_whitespace(arg))
	{
		av = ft_calloc(sizeof(char *), 2);
		if (!av)
			return (NULL);
		av[0] = ft_strdup(arg);
		av[1] = NULL;
		return (av);
	}
	arg_formatted = ft_strdup(arg);
	if (!arg_formatted)
		return (NULL);
	arg_formatted = format_arg(arg_formatted);
	av = ft_split(arg_formatted, -1);
	free(arg_formatted);
	return (av);
}

static int	nothing_but_whitespace(char *arg)
{
	while (*arg)
	{
		if (!ft_isspace(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static char	*format_arg(char *arg_f)
{
	const char	*escapeable;
	size_t		i;

	escapeable = "\\ \'";
	i = 0;
	while (arg_f[i])
	{
		if (arg_f[i] == '\\' && ft_strchr(escapeable, arg_f[i + 1]))
			erase_char(&(arg_f[i]));
		else if (arg_f[i] == '\'' && find_matching_quote(&arg_f[i]))
		{
			erase_char(&(arg_f[i]));
			i += find_matching_quote(&arg_f[i]) - &arg_f[i];
			erase_char(&(arg_f[i]));
		}
		else if (arg_f[i] == ' ')
			arg_f[i] = -1;
		i++;
	}
	return (arg_f);
}

static void	erase_char(char *s)
{
	ft_memmove(s, s + 1, ft_strlen(s));
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
