/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:47:53 by juaho             #+#    #+#             */
/*   Updated: 2025/01/27 16:28:31 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../inc/pipex_bonus.h"

void	first_cmd(char *infile, char *arg, t_pipex *px)
{
	char	**av;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
		error_exit(px, NULL);
	if (cpid)
		return ;
	open_infile(infile, px);
	av = get_av(arg, px);
	if (dup2(px->fd, STDIN_FILENO) < 0
		|| dup2(px->pipe_fd[WRITE], STDOUT_FILENO) < 0)
	{
		perror("first_cmd: dup2");
		free_av(&av);
		close_pipex(px);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px);
}

void	cmd(char *arg, t_pipex *px)
{
	char	**av;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
		error_exit(px, NULL);
	if (cpid)
		return ;
	av = get_av(arg, px);
	if (dup2(px->prev_pipe_fd, STDIN_FILENO) < 0
		|| dup2(px->pipe_fd[WRITE], STDOUT_FILENO) < 0)
	{
		perror("cmd: dup2");
		free_av(&av);
		close_pipex(px);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px);
}

void	last_cmd(char *outfile, char *arg, t_pipex *px)
{
	char	**av;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
		error_exit(px, NULL);
	if (cpid)
		return ;
	open_outfile(outfile, px);
	av = get_av(arg, px);
	if (dup2(px->prev_pipe_fd, STDIN_FILENO) < 0
		|| dup2(px->fd, STDOUT_FILENO) < 0)
	{
		perror("last_cmd: dup2");
		free_av(&av);
		close_pipex(px);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px);
}
