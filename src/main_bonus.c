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

static int		exec_commands(int argc, char **argv, t_pipex *px, int heredoc);
static int		wait_for_children(pid_t last_pid, size_t n);
static void		mid_cmd(char *arg, t_pipex *px);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		exit_code;
	int		heredoc;

	heredoc = 0;
	if (argc < 5)
	{
		ft_putstr_fd("Usage: [infile] <2+ cmds> [outfile]\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		heredoc = 1;
	if (heredoc == 1 && argc < 6)
	{
		ft_putstr_fd("Usage: here_doc [lim] <2+ cmds> [outfile]\n", 2);
		return (1);
	}
	init_pipex(&px, envp);
	exit_code = exec_commands(argc, argv, &px, heredoc);
	close_pipex(&px, exit_code);
}

static int	exec_commands(int argc, char **argv, t_pipex *px, int heredoc)
{
	int		cmd;
	pid_t	last_pid;

	cmd = 2 + heredoc;
	if (heredoc)
		heredoc_first_cmd(argv[2], argv[cmd++], px);
	else
		first_cmd(argv[1], argv[cmd++], px);
	roll_pipe(px, 0);
	while (cmd < argc - 2)
	{
		mid_cmd(argv[cmd], px);
		roll_pipe(px, cmd + 1 >= argc - 2);
		cmd++;
	}
	if (heredoc)
		last_pid = heredoc_last_cmd(argv[argc - 1], argv[argc - 2], px);
	else
		last_pid = last_cmd(argv[argc - 1], argv[argc - 2], px);
	close_all_fds(px);
	return (wait_for_children(last_pid, argc - 3 - heredoc));
}

static int	wait_for_children(pid_t last_pid, size_t n)
{
	pid_t	cpid;
	int		wstatus;
	int		exit_status;

	exit_status = 0;
	while (n)
	{
		cpid = waitpid(-1, &wstatus, 0);
		if (cpid > 0)
		{
			if (cpid == last_pid && WIFEXITED(wstatus))
				exit_status = WEXITSTATUS(wstatus);
			n--;
		}
	}
	return (exit_status);
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
