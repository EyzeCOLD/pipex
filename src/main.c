/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:04:53 by juaho             #+#    #+#             */
/*   Updated: 2025/01/22 11:08:07 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../inc/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc < 5)
		return (1);
	int	p_fd[2];

	if (init_pipex(&px, envp) < 0)
	{
		perror("pipex");
		close_pipex(&px);
	}
	if (exec_fork_first(argv[2], argv[1], &px) < 0)
		close_pipex(&px);
	exec_fork_last(argv[3], argv[4], &px);
	close_pipex(&px);
}
