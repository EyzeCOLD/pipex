/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:11:51 by juaho             #+#    #+#             */
/*   Updated: 2025/01/24 11:30:16 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../inc/pipex_bonus.h"

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
	fd_bzero(px);
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
			error = -1;
	if (px->pipe_fd[WRITE] != -1)
		if (close(px->pipe_fd[WRITE]) < 0)
			error = -1;
	if (px->prev_pipe_fd != -1)
		if (close(px->prev_pipe_fd) < 0)
			error = -1;
	fd_bzero(px);
	return (error);
}

int	close_pipex(t_pipex *px)
{
	if (px->env_path)
		free_av(&(px->env_path));
	free(px->pwd);
	if (close_all_fds(px) < 0)
	{
		perror("close_pipex");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	roll_pipe(t_pipex *px, int last)
{
	if (px->prev_pipe_fd != -1)
		close(px->prev_pipe_fd);
	close(px->pipe_fd[WRITE]);
	px->pipe_fd[WRITE] = -1;
	px->prev_pipe_fd = px->pipe_fd[READ];
	if (last)
	{
		if (pipe(px->pipe_fd) < 0)
		{
			perror("roll pipe");
			close_pipex(px);
		}
	}
}
