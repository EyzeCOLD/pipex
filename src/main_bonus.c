/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:43:41 by juaho             #+#    #+#             */
/*   Updated: 2025/01/28 11:23:10 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static void	exec_commands(int argc, char **argv, t_pipex *px);
static void	mid_cmd(char *arg, t_pipex *px);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: [infile] <2+ cmds> [outfile]\n", 2);
		return (-1);
	}
	if (init_pipex(&px, envp) < 0)
	{
		perror("pipex");
		close_pipex(&px);
	}
	exec_commands(argc, argv, &px);
	close_pipex(&px);
	return (0);
}

static void	exec_commands(int argc, char **argv, t_pipex *px)
{
	int	argn;

	first_cmd(argv[1], argv[2], px);
	roll_pipe(px, 0);
	argn = 3;
	while (argn < argc - 2)
	{
		mid_cmd(argv[argn], px);
		if (argn + 1 < argc - 2)
			roll_pipe(px, 0);
		else
			roll_pipe(px, 1);
		argn++;
	}
	last_cmd(argv[argc - 1], argv[argn], px);
	close_all_fds(px);
	argn = 3;
	while (argn++ < argc)
		wait(NULL);
}

static void	mid_cmd(char *arg, t_pipex *px)
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
		perror("mid_cmd: dup2");
		free_av(&av);
		close_pipex(px);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px);
}
