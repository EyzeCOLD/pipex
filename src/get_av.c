/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:14:03 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 09:26:27 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static char	*search_env(char *executable, char **env_path);

char **get_av(char *arg, char **env_path, char *pwd)
{
	char **av;
	char *full_path;

	av = arg_split(arg);
	if (!av)
		return (NULL);
	if (**av == '/')
		return (av);
	if (**av == '.')
		full_path = ft_strjoinm(3, pwd, "/", *av);
	else
		full_path = search_env(*av, env_path);
	if (!full_path)
	{
		free_av(&av);
		return (NULL);
	}
	free(*av);
	*av = full_path;
	return (av);
}

static char	*search_env(char *executable, char **env_path)
{
	char	*full_path;

	while (*env_path)
	{
		full_path = ft_strjoinm(3, *env_path, "/", executable);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		env_path++;
	}
	return (NULL);
}
