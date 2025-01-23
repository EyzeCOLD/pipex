/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:33:46 by juaho             #+#    #+#             */
/*   Updated: 2025/01/23 10:14:31 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../inc/pipex.h"

static void	first_cmd(char *infile, char *arg, t_pipex *px);
static void	last_cmd(char *outfile, char *arg, t_pipex *px);

void	exec_commands(char **argv, t_pipex *px)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
	{
		perror("pipex");
		close_pipex(px);
	}
	if (cpid == 0)
		first_cmd(argv[1], argv[2], px);
	wait(NULL);
	close(px->p_fd[WRITE]);
	px->p_fd[WRITE] = -1;
	last_cmd(argv[4], argv[3], px);
}

static void	first_cmd(char *infile, char *arg, t_pipex *px)
{
	char	**av;

	open_infile(infile, px);
	av = get_av(arg, px);
	if (dup2(px->fd, 0) < 0 || dup2(px->p_fd[WRITE], 1) < 0)
	{
		perror("pipex");
		free_av(&av);
		close_pipex(px);
	}
	close(px->fd);
	close(px->p_fd[WRITE]);
	close(px->p_fd[READ]);
	px->fd = -1;
	execve(*av, av, px->envp);
	perror("pipex: execve");
	free_av(&av);
	close_pipex(px);
}

static void	last_cmd(char *outfile, char *arg, t_pipex *px)
{
	char	**av;

	open_outfile(outfile, px);
	av = get_av(arg, px);
	if (dup2(px->p_fd[READ], 0) < 0 || dup2(px->fd, 1) < 0)
	{
		perror("pipex");
		free_av(&av);
		close_pipex(px);
	}
	close(px->fd);
	close(px->p_fd[WRITE]);
	close(px->p_fd[READ]);
	px->fd = -1;
	execve(*av, av, px->envp);
	perror("pipex: execve");
	free_av(&av);
	close_pipex(px);
}
