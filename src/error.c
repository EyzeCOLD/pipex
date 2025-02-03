/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:06:11 by juaho             #+#    #+#             */
/*   Updated: 2025/01/28 11:19:05 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../inc/pipex.h"

int	err_cmd_not_found(char *cmd)
{
	char	*emsg;

	emsg = ft_strjoinm(3, "pipex: ", cmd, ": command not found");
	if (!emsg)
		return (-1);
	ft_putendl_fd(emsg, 2);
	free(emsg);
	return (127);
}

int	err_perm_denied(char *cmd)
{
	char	*emsg;

	emsg = ft_strjoinm(3, "pipex: ", cmd, ": Permission denied");
	if (!emsg)
		return (-1);
	ft_putendl_fd(emsg, 2);
	free(emsg);
	return (126);
}

int	err_with_filename(char *filename)
{
	char	*emsg;

	emsg = ft_strjoinm(4, "pipex: ", filename, ": ", strerror(errno));
	if (!emsg)
		return (-1);
	ft_putendl_fd(emsg, 2);
	free(emsg);
	return (errno);
}

void	error_exit(t_pipex *px, char *filename)
{
	if (filename)
		err_with_filename(filename);
	else
		perror("pipex");
	close_pipex(px, 0);
}
