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
	last_cmd(argv[3], argv[4]), px);
}

void	first_cmd(char *infile, char *arg, t_pipex *px)
{
	char	**av;
	int		infile_fd;

	infile_fd = open_infile(infile, px);
	av = get_av(arg, px);
	if (dup2(infile_fd, 0) < 0 || dup2(px->p_fd[WRITE], 1) < 0)
	{
		perror("pipex");
		free_av(&av);
		close(infile_fd);
		close_pipex(px);
	}
	close(infile_fd);
	execve(*av, av, px->envp);
