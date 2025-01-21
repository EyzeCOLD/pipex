/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:04:53 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 15:16:55 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../inc/pipex.h"

static int	exec_fork_first(char *cmd, char *infile, t_pipex *px);
static int	exec_first_child(char *cmd, char *infile, t_pipex *px);
static int	exec_fork_last(char *cmd, char *outfile, t_pipex *px);

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

static int	exec_fork_first(char *cmd, char *infile, t_pipex *px)
{
	int	cpid;

	cpid = fork();
	if (cpid < 0)
		return (-1);
	if (cpid == 0)
		exec_first_child(cmd, infile, px);
	wait(NULL);
	return (0);
}

static int	exec_first_child(char *cmd, char *infile, t_pipex *px)
{
	char	*infile_path;
	char	**av;
	int		infile_fd;

	infile_path = ft_strjoinm(3, px->pwd, "/", infile);
	if (!infile_path)
		return (-1);
	infile_fd = open(infile_path, O_RDONLY);
	if (infile_fd < 0)
	{
		err_with_filename(infile);
		return (-2);
	}
	av = get_av(cmd, px->env_path, px->pwd);
	if (!av)
	{
		
static int	exec_fork_last(char *cmd, char *outfile, t_pipex *px);
