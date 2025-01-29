/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:11:51 by juaho             #+#    #+#             */
/*   Updated: 2025/01/28 11:17:57 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "../inc/pipex.h"

int	init_pipex(t_pipex *px, char **envp)
{
	fd_bzero(px);
	px->envp = envp;
	px->env_path = NULL;
	px->pwd = NULL;
	if (*envp)
	{
		if (get_env_line("PATH=", envp))
		{
			px->env_path = get_env_path(envp);
			if (!px->env_path)
				return (-1);
		}
		px->pwd = get_env_line("PWD=", envp);
	}
	if (pipe(px->pipe_fd) < 0)
		return (-1);
	return (0);
}

void	fd_bzero(t_pipex *px)
{
	px->pipe_fd[READ] = -1;
	px->pipe_fd[WRITE] = -1;
	px->fd = -1;
	px->prev_pipe_fd = -1;
}

int	close_all_fds(t_pipex *px)
{
	int	error;

	error = 0;
	if (px->fd != -1)
		if (close(px->fd) < 0)
			error = -1;
	if (px->pipe_fd[READ] != -1)
		if (close(px->pipe_fd[READ]) < 0)
			error = -2;
	if (px->pipe_fd[WRITE] != -1)
		if (close(px->pipe_fd[WRITE]) < 0)
			error = -3;
	if (px->prev_pipe_fd != -1)
		if (close(px->prev_pipe_fd) < 0)
			error = -4;
	fd_bzero(px);
	return (error);
}

int	close_pipex(t_pipex *px, int exit_status)
{
	int	error;
	int	close_err;

	error = errno;
	if (access(".tmp", F_OK) == 0)
		unlink(".tmp");
	if (px->env_path)
		free_av(&(px->env_path));
	close_err = close_all_fds(px);
	if (close_err < 0)
	{
		perror("close_pipex");
		exit(error);
	}
	if (exit_status)
		exit(exit_status);
	exit(error);
}

void	roll_pipe(t_pipex *px, int last)
{
	if (px->prev_pipe_fd != -1)
		close(px->prev_pipe_fd);
	close(px->pipe_fd[WRITE]);
	px->pipe_fd[WRITE] = -1;
	px->prev_pipe_fd = px->pipe_fd[READ];
	px->pipe_fd[READ] = -1;
	if (last)
		return ;
	if (pipe(px->pipe_fd) < 0)
	{
		perror("roll pipe");
		close_pipex(px, 0);
	}
}
