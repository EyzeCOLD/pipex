/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:43:41 by juaho             #+#    #+#             */
/*   Updated: 2025/01/28 11:25:34 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static int	exec_commands(int argc, char **argv, t_pipex *px);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: [infile] [cmd1] [cmd2] [outfile]\n", 2);
		return (-1);
	}
	if (init_pipex(&px, envp) < 0)
	{
		perror("pipex");
		close_pipex(&px, 0);
	}
	exit_status = exec_commands(argc, argv, &px);
	close_pipex(&px, exit_status);
}

static int	exec_commands(int argc, char **argv, t_pipex *px)
{
	int	wstatus;
	int	ret;

	first_cmd(argv[1], argv[2], px);
	roll_pipe(px, 0);
	last_cmd(argv[argc - 1], argv[3], px);
	close_all_fds(px);
	ret = 0;
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		ret = WEXITSTATUS(wstatus);
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		if (ret == 0)
			ret = WEXITSTATUS(wstatus);
	return (ret);
}
