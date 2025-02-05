/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:45:15 by juaho             #+#    #+#             */
/*   Updated: 2025/02/04 14:58:47 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

void	get_heredoc_input(char *lim, t_pipex *px)
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
		if (ft_putstr_fd(line, px->pipe_fd[1]) < 0)
		{
			free(line);
			error_exit(px, NULL);
		}
		free(line);
	}
	free(line);
}

pid_t	heredoc_last_cmd(char *outfile, char *arg, t_pipex *px)
{
	char	**av;
	pid_t	cpid;

	cpid = fork();
	if (cpid < 0)
		error_exit(px, NULL);
	if (cpid)
		return (cpid);
	open_file(outfile, px, O_WRONLY | O_APPEND | O_CREAT);
	av = get_av(arg, px);
	if (dup2(px->prev_pipe_fd, STDIN_FILENO) < 0
		|| dup2(px->fd, STDOUT_FILENO) < 0)
	{
		perror("last_cmd: dup2");
		free_av(&av);
		close_pipex(px, 0);
	}
	cmd_exec(av, px);
	return (-1);
}
