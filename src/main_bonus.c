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
#include "../inc/heredoc.h"
#include "../libft/libft.h"

static void	exec_commands(int argc, char **argv, t_pipex *px, int heredoc);
static void	mid_cmd(char *arg, t_pipex *px);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (init_pipex(&px, envp) < 0)
	{
		perror("pipex");
		close_pipex(&px, 0);
	}
	if (argc < 5)
	{
		ft_putstr_fd("Usage: [infile] <2+ cmds> [outfile]\n", 2);
		close_pipex(&px, 0);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("Usage: here_doc [lim] <2+ cmds> [outfile]\n", 2);
			close_pipex(&px, 0);
		}
		exec_commands(argc, argv, &px, 1);
	}
	else
		exec_commands(argc, argv, &px, 0);
	close_pipex(&px, 0);
}

static void	exec_commands(int argc, char **argv, t_pipex *px, int heredoc)
{
	int	argn;

	if (heredoc)
		heredoc_first_cmd(argv[2], argv[3], px);
	else
		first_cmd(argv[1], argv[2], px);
	roll_pipe(px, 0);
	argn = 3 + heredoc;
	while (argn < argc - 2)
	{
		mid_cmd(argv[argn], px);
		roll_pipe(px, argn + 1 >= argc - 2);
		argn++;
	}
	if (heredoc)
		heredoc_last_cmd(argv[argc - 1], argv[argc - 2], px);
	else
		last_cmd(argv[argc - 1], argv[argc - 2], px);
	close_all_fds(px);
	argn = 3 + heredoc;
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
		close_pipex(px, 0);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px, 0);
}
