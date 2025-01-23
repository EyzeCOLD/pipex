/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:11:51 by juaho             #+#    #+#             */
/*   Updated: 2025/01/22 11:07:25 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../inc/pipex.h"

int	init_pipex(t_pipex *px, char **envp)
{
	px->envp = envp;
	px->env_path = NULL;
	px->pwd = NULL;
	px->env_path = get_env_path(envp);
	if (!px->env_path)
		return (-1);
	px->pwd = get_pwd(envp);
	if (!px->pwd)
		return (-1);
	if (pipe(px->p_fd) < 0)
		return (-1);
	px->fd = -1;
	return (0);
}

int	close_pipex(t_pipex *px)
{
	int	error;

	if (px->env_path)
		free_av(&(px->env_path));
	free(px->pwd);
	error = 0;
	if (px->p_fd[READ] != -1)
		if (close(px->p_fd[READ]) < 0)
			error = -1;
	if (px->p_fd[WRITE] != -1)
		if (close(px->p_fd[WRITE]) < 0)
			error = -1;
	if (px->fd != -1)
		if (close(px->fd) < 0)
			error = -1;
	if (error < 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
