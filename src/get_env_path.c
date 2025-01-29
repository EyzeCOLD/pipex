/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:33:19 by juaho             #+#    #+#             */
/*   Updated: 2025/01/19 12:41:45 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/pipex.h"

char	**get_env_path(char **envp)
{
	char	*env_line;
	char	**ret;

	env_line = get_env_line("PATH=", envp);
	if (!env_line)
		return (NULL);
	ret = ft_split(env_line, ':');
	return (ret);
}

char	*get_env_line(char *line, char **envp)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	while (*envp)
	{
		if (ft_strncmp(*envp, line, ft_strlen(line)) == 0)
			return (*envp + line_len);
		envp++;
	}
	return (NULL);
}
