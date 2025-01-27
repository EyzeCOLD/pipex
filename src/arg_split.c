/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:26:10 by juaho             #+#    #+#             */
/*   Updated: 2025/01/19 22:25:25 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

static size_t	count_elms(char *arg);
static void		populate_array(char **av, char *arg);

char	**arg_split(char *arg)
{
	char	**av;
	size_t	elms;

	elms = count_elms(arg);
	if (elms == 0)
	{
		av = (char **) ft_calloc(sizeof(char *), 2);
		if (!av)
			return (NULL);
		av[0] = ft_strdup(arg);
		return (av);
	}
	av = (char **) ft_calloc(sizeof(char *), elms + 1);
	if (!av)
		return (NULL);
	populate_array(av, arg);
	return (av);
}

void	free_av(char ***av)
{
	char	**ptr;

	ptr = *av;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(*av);
	*av = NULL;
}

static size_t	count_elms(char *arg)
{
	size_t	elms;

	elms = 0;
	while (*arg)
	{
		if (*arg != ' ')
		{
			elms++;
			while (*arg != ' ' && *arg != '\0')
			{
				if (*arg == '\\' && *(arg + 1) == ' ')
					arg++;
				arg++;
			}
		}
		else
			arg++;
	}
	return (elms);
}

static void	populate_array(char **av, char *arg)
{
	char	*end;

	while (*arg)
	{
		if (*arg != ' ')
		{
			end = arg;
			while (*end != ' ' && *end != '\0')
			{
				if (*end == '\\' && *(end + 1) == ' ')
					end++;
				end++;
			}
			*av = ft_substr(arg, 0, end - arg);
			if (!*av)
			{
				free_av(&av);
				break ;
			}
			av++;
			arg = end;
		}
		else
			arg++;
	}
}
