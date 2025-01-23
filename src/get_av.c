/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_av.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:14:03 by juaho             #+#    #+#             */
/*   Updated: 2025/01/22 11:20:41 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static char	*search_env(char *cmd, t_pipex *px);
static void	check_full_path(char *path, char ***av, t_pipex *px);

char **get_av(char *arg, t_pipex *px)
{
	char **av;
	char *full_path;

	av = arg_split(arg);
	if (!av)
		return (NULL);
	if (**av == '/')
		return (av);
	if (**av == '.')
		full_path = ft_strjoinm(3, px->pwd, "/", *av);
	else
		full_path = search_env(*av, px);
	if (!full_path)
	{
		free_av(&av);
		return (NULL);
	}
	check_full_path(full_path, &av, px);
	free(*av);
	*av = full_path;
	return (av);
}

static char	*search_env(char *cmd, t_pipex *px)
{
	char	*full_path;
	size_t	i;

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
	err_cmd_not_found(cmd);
	free(full_path);
	close_pipex(px);
	return (NULL);
}

static void	check_full_path(char *path, char ***av, t_pipex *px)
{
	if (access(path, X_OK) < 0)
	{
		err_with_filename(**av);
		free_av(av);
		free(path);
		close_pipex(px);
	}
}
