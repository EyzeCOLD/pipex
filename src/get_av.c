/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_av.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:14:03 by juaho             #+#    #+#             */
/*   Updated: 2025/02/04 15:03:17 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static char	*search_env(char *cmd, t_pipex *px);

char	**get_av(char *arg, t_pipex *px)
{
	char	**av;
	char	*full_path;

	av = arg_split(arg);
	if (!av)
		return (NULL);
	else if (ft_strchr(*av, '/') == 0)
	{
		full_path = search_env(*av, px);
		if (!full_path)
		{
			perror("pipex");
			close_pipex(px, 0);
		}
		if (*full_path != '/')
		{
			err_cmd_not_found(*av);
			free_av(&av);
			free(full_path);
			close_pipex(px, 127);
		}
		free(*av);
		*av = full_path;
	}
	return (av);
}

static char	*search_env(char *cmd, t_pipex *px)
{
	char	*full_path;
	size_t	i;

	if (*cmd == '\0' || !px->env_path)
		return (ft_strdup(cmd));
	i = 0;
	while (px->env_path[i])
	{
		full_path = ft_strjoinm(3, px->env_path[i], "/", cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (ft_strdup(cmd));
}
