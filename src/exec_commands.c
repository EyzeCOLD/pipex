/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:33:46 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 15:16:14 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "../inc/pipex.h"

static int	fork_exec(char **av, int *in_fd, int *out_fd, char **envp);
static int	fork_exec_child(char **av, int *in_fd, int *out_fd, char **envp);

int	exec_commands(size_t cmds, t_pipex *px, char **envp)
{
	char	***av_arr;
	size_t	i;
	int		*in_fd;
	int		*out_fd;

	av_arr = px->av_arr;
	in_fd = &px->infile_fd;
	out_fd = &px->pipe_arr[0][WRITE];
	if (fork_exec(*av_arr, in_fd, out_fd, envp) < 0)
		return (-1);
	i = 0;
	while (i < cmds - 2)
	{
		av_arr++;
		in_fd = &px->pipe_arr[i][READ];
		out_fd = &px->pipe_arr[i + 1][WRITE];
		if (fork_exec(*av_arr, in_fd, out_fd, envp) < 0)
			return (-1);
		i++;
	}
	av_arr++;
	in_fd = &px->pipe_arr[i][READ];
	out_fd = &px->outfile_fd;
	return (fork_exec(*av_arr, in_fd, out_fd, envp));
}

static int	fork_exec(char **av, int *in_fd, int *out_fd, char **envp)
{
	pid_t	cpid;
	int		wstatus;

	if (access(*av, X_OK) < 0)
		return (-1);
	cpid = fork();
	if (cpid < 0)
		return (-1);
	if (cpid == 0)
		return (fork_exec_child(av, in_fd, out_fd, envp));
	wait(&wstatus);
	if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
		return (-1);
	if (close(*in_fd) < 0 || close(*out_fd) < 0)
		return (-1);
	*in_fd = -1;
	*out_fd = -1;
	return (0);
}

static int	fork_exec_child(char **av, int *in_fd, int *out_fd, char **envp)
{
	if (dup2(*in_fd, 0) < 0 || dup2(*out_fd, 1) < 0)
		return (-1);
	if (close(*in_fd) < 0 || close(*out_fd) < 0)
		return (-1);
	*in_fd = -1;
	*out_fd = -1;
	execve(*av, av, envp);
	return (-1);
}
