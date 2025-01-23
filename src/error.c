/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:06:11 by juaho             #+#    #+#             */
/*   Updated: 2025/01/22 09:46:18 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../inc/pipex.h"

void	err_cmd_not_found(char *cmd)
{
	char *emsg;

	emsg = ft_strjoin("command not found: ", cmd);
	if (!emsg)
		return ;
	ft_putendl_fd(emsg, 2);
	free(emsg);
}

void	err_with_filename(char *filename)
{
	char *emsg;

	emsg = ft_strjoinm(3, strerror(errno), ": ", filename);
	if (!emsg)
		return ;
	ft_putendl_fd(emsg, 2);
	free(emsg);
}

void	error_exit(t_pipex *px)
{
	perror("pipex");
	close_pipex(px);
}
