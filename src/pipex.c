/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:25:19 by juaho             #+#    #+#             */
/*   Updated: 2025/01/15 13:24:26 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../inc/pipex.h"

static int	init_fd_cont(t_fd_cont *fdc, size_t pipes);
static void	free_and_exit(t_fd_cont *fdc, char **av);
static void	exec_commands(t_fd_cont *fdc, char **argv, char **envp);

int main(int argc, char **argv, char **envp)
{
	if (argc > 4)
	{
		t_fd_cont	fdc;

		if (init_fd_cont(&fdc, argc - 4) == -1)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (open_files(argc, argv, envp, &fdc) == -1)
		{
			perror("open_files");
			free_and_exit(&fdc, NULL);
		}
		exec_commands(&fdc, argv, envp);
		close_and_free_fd_cont(&fdc);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static void	exec_commands(t_fd_cont *fdc, char **argv, char **envp)
{
	char	**av;

	av = arg_to_av_for_execve(argv[2], envp);
	if (!av)
	{
		perror("cmd1 path");
		free_and_exit(fdc, NULL);
	}
	if (fork_exec(av, fdc->infile, fdc->pipearr[0][1], fdc) == -1)
		free_and_exit(fdc, av);
	free_arr(&av);
	av = arg_to_av_for_execve(argv[3], envp);
	if (!av)
	{
		perror("cmd2 path");
		free_and_exit(fdc, NULL);
	}
	if (fork_exec(av, fdc->pipearr[0][0], fdc->outfile, fdc) == -1)
		free_and_exit(fdc, av);
	free_arr(&av);
}

static void	free_and_exit(t_fd_cont *fdc, char **av)
{
	if (av)
		free_arr(&av);
	close_and_free_fd_cont(fdc);
	exit(EXIT_FAILURE);
}

static int	init_fd_cont(t_fd_cont *fdc, size_t pipes)
{
	fdc->pipearr = pipe_array(pipes);
	if (!fdc->pipearr)
		return (-1);
	fdc->pipes = pipes;
	fdc->infile = -1;
	fdc->outfile = -1;
	return (0);
}

void	close_and_free_fd_cont(t_fd_cont *fdc)
{
	close_and_free_pipe_arr(&(fdc->pipearr), fdc->pipes);
	close(fdc->infile);
	close(fdc->outfile);
}
