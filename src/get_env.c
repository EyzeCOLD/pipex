/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:23:39 by juaho             #+#    #+#             */
/*   Updated: 2025/01/15 12:21:07 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static char	*get_env_line(char *line, char **envp)
{
	size_t	len;

	len = ft_strlen(line);
	while (*envp)
	{
		if (ft_strncmp(*envp, line, len) == 0)
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	*get_pwd(char **envp)
{
	char	*pwd_line;

	pwd_line = get_env_line("PWD=", envp);
	if (!pwd_line)
		return (NULL);
	return (ft_strdup(pwd_line + 4));
}

char	**env_path_split(char **envp)
{
	char	*path_line;

	path_line = get_env_line("PATH=", envp);
	if (!path_line)
		return (NULL);
	return (ft_split(path_line + 5, ':'));
}
