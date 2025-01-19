/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:14:03 by juaho             #+#    #+#             */
/*   Updated: 2025/01/19 22:26:29 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static char **get_av(char *arg, char **env_path, char *pwd);
static char	*search_env(char *executable, char **env_path);

char	***get_av_arr(int argc, char **argv, char **env_path, char *pwd)
{
	char	***av_arr;
	size_t	i;
	size_t	cmds;

	cmds = argc - 3;
	av_arr = (char ***) ft_calloc(sizeof(char **), cmds + 1);
	if (!av_arr)
		return (NULL);
	i = 0;
	while (i < cmds)
	{
		av_arr[i] = get_av(argv[2 + i], env_path, pwd);
		if (!av_arr[i])
		{
			free_av_arr(&av_arr);
			return (NULL);
		}
		i++;
	}
	return (av_arr);
}

void	free_av_arr(char ****av_array)
{
	char	***ptr;

	ptr = *av_array;
	while (*ptr)
	{
		free_av(ptr);
		*ptr = NULL;
		ptr++;
	}
	free(*av_array);
	*av_array = NULL;
}
		

static char **get_av(char *arg, char **env_path, char *pwd)
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
