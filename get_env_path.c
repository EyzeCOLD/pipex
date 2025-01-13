/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:23:39 by juaho             #+#    #+#             */
/*   Updated: 2025/01/11 11:31:47 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*get_env_line(char *line, char **envp)
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
