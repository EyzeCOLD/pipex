/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:47:53 by juaho             #+#    #+#             */
/*   Updated: 2025/01/24 11:32:44 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../inc/pipex_bonus.h"

static void	first_cmd(char *infile, char *arg, t_pipex *px);
static void	cmd(char *arg, t_pipex *px);
static void	last_cmd(char *outfile, char *arg, t_pipex *px);

void	exec_commands(int argc, char **argv, t_pipex *px)
{
	int		i;

	first_cmd(argv[1], argv[2], px);
	wait(NULL);
	roll_pipe(px, argc - 5);
	i = 1;
	while (i < argc - 4)
	{
		cmd(argv[i + 2], px);
		wait(NULL);
		roll_pipe(px, (i + 1 < argc - 4));
		i++;
	}
	last_cmd(argv[argc - 1], argv[i + 2], px);
}

static void	first_cmd(char *infile, char *arg, t_pipex *px)
{
	char	**av;
	int		cpid;

	cpid = fork();
	if (cpid < 0)
	{
		perror("cmd: fork");
		close_pipex(px);
	}
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
	perror("first_cmd: execve");
	free_av(&av);
	close_pipex(px);
}

static void	cmd(char *arg, t_pipex *px)
{
	char	**av;
	int		cpid;

	cpid = fork();
	if (cpid < 0)
	{
		perror("cmd: fork");
		close_pipex(px);
	}
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
	perror("cmd: execve");
	free_av(&av);
	close_pipex(px);
}

static void	last_cmd(char *outfile, char *arg, t_pipex *px)
{
	char	**av;

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
	perror("last_cmd: execve");
	free_av(&av);
	close_pipex(px);
}
