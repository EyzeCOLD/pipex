/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:43:41 by juaho             #+#    #+#             */
/*   Updated: 2025/02/04 14:55:27 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static int	exec_commands(int argc, char **argv, t_pipex *px);
static int	wait_for_children(pid_t last_pid);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: [infile] [cmd1] [cmd2] [outfile]\n", 2);
		return (1);
	}
	init_pipex(&px, envp);
	exit_status = exec_commands(argc, argv, &px);
	close_pipex(&px, exit_status);
}

static int	exec_commands(int argc, char **argv, t_pipex *px)
{
	pid_t	last_pid;

	first_cmd(argv[1], argv[2], px);
	roll_pipe(px, 1);
	last_pid = last_cmd(argv[argc - 1], argv[3], px);
	close_all_fds(px);
	return (wait_for_children(last_pid));
}

static int	wait_for_children(pid_t last_pid)
{
	size_t	children_left;
	int		exit_status;
	int		wstatus;
	pid_t	cpid;

	children_left = 2;
	exit_status = 0;
	while (children_left)
	{
		cpid = wait(&wstatus);
		if (cpid == last_pid && WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		children_left--;
	}
	return (exit_status);
}
