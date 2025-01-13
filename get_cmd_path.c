/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:10:30 by juaho             #+#    #+#             */
/*   Updated: 2025/01/13 20:04:26 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

static char	*search_env_path(char *cmd, char **env_path);
static char *search_pwd(char *cmd, char **envp);

int	expand_cmd_path(char **cmd, char **envp)
{
	char	*ptr;

	ptr = *cmd;
	if (ptr[0] != '/')
	{
		if (ft_strncmp(ptr, "./", 2) == 0 || ft_strncmp(ptr + 1, "./", 2) == 0)
			*cmd = search_pwd(ptr, envp);
		else
			*cmd = search_env_path(ptr, envp);
		free(ptr);
		if (!*cmd)
			return (-1);
		return (0);
	}
	return (0);
}

static char	*search_pwd(char *cmd, char **envp)
{
	char	*full_path;
	char	*pwd;

	pwd = get_pwd(envp);
	if (!pwd)
		return (NULL);
	full_path = ft_strjoinm(3, pwd, "/", cmd);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	return (NULL);
}

static char	*search_env_path(char *cmd, char **envp)
{
	char	*full_path;
	char	**env_path;

	env_path = get_path_arr(envp);
	if (!env_path)
		return (NULL);
	full_path = NULL;
	while (*env_path)
	{
		full_path = ft_strjoinm(3, *env_path, "/", cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		env_path++;
	}
	return (full_path);
}
