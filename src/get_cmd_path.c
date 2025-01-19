/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:10:30 by juaho             #+#    #+#             */
/*   Updated: 2025/01/14 10:55:28 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/pipex.h"
#include <unistd.h>

static char	*search_env_path(char *cmd, char **env_path);
static int	expand_cmd_path(char **cmd, char **envp);

char	**arg_to_av_for_execve(char *arg, char **envp)
{
	char	**av;

	av = cmd_split(arg);
	if (!av)
		return (NULL);
	if (expand_cmd_path(av, envp) == -1)
	{
		free_arr(&av);
		return (NULL);
	}
	return (av);
}

static int	expand_cmd_path(char **cmd, char **envp)
{
	char	*ptr;

	ptr = *cmd;
	if (ptr[0] != '/')
	{
		if (ft_strncmp(ptr, "./", 2) == 0 || ft_strncmp(ptr + 1, "./", 2) == 0)
			*cmd = get_full_filepath(ptr, envp);
		else
			*cmd = search_env_path(ptr, envp);
		free(ptr);
		if (!*cmd)
			return (-1);
		return (0);
	}
	return (0);
}

char	*get_full_filepath(char *file, char **envp)
{
	char	*full_path;
	char	*pwd;

	pwd = get_pwd(envp);
	if (!pwd)
		return (NULL);
	full_path = ft_strjoinm(3, pwd, "/", file);
	free(pwd);
	return (full_path);
}

static char	*search_env_path(char *cmd, char **envp)
{
	char	*full_path;
	char	**env_path;
	size_t	i;

	env_path = env_path_split(envp);
	if (!env_path)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (env_path[i])
	{
		if (full_path)
			free(full_path);
		full_path = ft_strjoinm(3, env_path[i], "/", cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
		i++;
	}
	free_arr(&env_path);
	return (full_path);
}
