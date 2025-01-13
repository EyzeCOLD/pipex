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

int	fork_exec(char **av, int in_fd, int out_fd, char **envp)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid > 0)
		wait(NULL);
	else
	{
		dup2(in_fd, 0);
		dup2(out_fd, 1);
		execve(*av, av, envp);
		perror("execve");
		return (-1);
	}
	close(in_fd);
	close(out_fd);
	return (0);
}
