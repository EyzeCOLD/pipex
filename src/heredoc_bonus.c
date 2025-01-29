/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:45:15 by juaho             #+#    #+#             */
/*   Updated: 2025/01/29 12:19:53 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static void	open_heredoc(char *lim, t_pipex *px);
static void	get_heredoc_input(char *lim, t_pipex *px);

void	heredoc_first_cmd(char *lim, char *arg, t_pipex *px)
{
	char	**av;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
		error_exit(px, NULL);
	if (cpid)
		return ;
	open_heredoc(lim, px);
	av = get_av(arg, px);
	if (dup2(px->fd, STDIN_FILENO) < 0
		|| dup2(px->pipe_fd[WRITE], STDOUT_FILENO) < 0)
	{
		perror("heredoc_cmd: dup2");
		free_av(&av);
		close_pipex(px, 0);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px, 0);
}

void	heredoc_last_cmd(char *outfile, char *arg, t_pipex *px)
{
	char	**av;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
		error_exit(px, NULL);
	if (cpid)
		return ;
	open_outfile(outfile, px, O_WRONLY | O_CREAT | O_APPEND);
	av = get_av(arg, px);
	if (dup2(px->prev_pipe_fd, STDIN_FILENO) < 0
		|| dup2(px->fd, STDOUT_FILENO) < 0)
	{
		perror("last_cmd: dup2");
		free_av(&av);
		close_pipex(px, 0);
	}
	close_all_fds(px);
	execve(*av, av, px->envp);
	err_with_filename(*av);
	free_av(&av);
	close_pipex(px, 0);
}

static void	open_heredoc(char *lim, t_pipex *px)
{
	px->fd = open(".tmp", O_CREAT | O_EXCL | O_WRONLY, 00644);
	if (px->fd < 0)
	{
		perror("heredoc tmpfile");
		close_pipex(px, 0);
	}
	get_heredoc_input(lim, px);
	close(px->fd);
	px->fd = open(".tmp", O_RDONLY);
	if (px->fd < 0)
	{
		perror("heredoc tmpfile");
		close_pipex(px, 0);
	}
}

static void	get_heredoc_input(char *lim, t_pipex *px)
{
	char	*line;
	size_t	lim_len;

	lim_len = ft_strlen(lim);
	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			error_exit(px, NULL);
		if (ft_strncmp(line, lim, lim_len) == 0 && line[lim_len] == '\n')
			break ;
		if (ft_putstr_fd(line, px->fd) < 0)
		{
			free(line);
			error_exit(px, NULL);
		}
		free(line);
	}
	free(line);
}
