/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:19:09 by juaho             #+#    #+#             */
/*   Updated: 2025/01/11 17:26:31 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/pipex.h"

int	fork_exec(char **av, int in_fd, int out_fd, t_fd_cont *fdc)
{
	pid_t	cpid;
	int		wstatus;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid > 0)
		wait(&wstatus);
	else
	{
		setbuf(stdout, NULL);
		printf("infd %d, outfd %d\n", in_fd, out_fd);
		printf("struct: infd %d, outfd %d\n, piper %d pipew %d\n", fdc->infile, fdc->outfile, fdc->pipearr[0][0], fdc->pipearr[0][1]);
		dup2(in_fd, 0);
		dup2(out_fd, 1);
		close_and_free_fd_cont(fdc);
		execve(*av, av, NULL);
		perror("execve");
		return (-1);
	}
	if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
		return (-1);
	return (0);
}
