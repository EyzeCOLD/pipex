/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:10:30 by juaho             #+#    #+#             */
/*   Updated: 2025/01/11 13:58:14 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>

static char	*search_env_path(char **cmd, char **env_path);

char	*get_cmd_path_for_execve(char **cmd, char **env_path)
{
	if (ft_strncmp(*cmd, "./", 2) == 0)
		return (ft_substr(*cmd, 2, ft_strlen(*cmd) - 2));
	else if (ft_strncmp(*cmd, "/", 1) == 0)
		return (ft_strdup(*cmd));
	else
		return (search_env_path(cmd, env_path));
}

static char	*search_env_path(char **cmd, char **env_path)
{
	char	*full_path;

	full_path = NULL;
	while (*env_path)
	{
		full_path = ft_strjoinm(3, *env_path, "/", *cmd);
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
