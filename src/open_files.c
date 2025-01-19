/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:51:31 by juaho             #+#    #+#             */
/*   Updated: 2025/01/15 16:07:53 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../inc/pipex.h"

static int	open_infile(char *infile, char **envp);
static int	open_outfile(char *outfile, char **envp);

int	open_files(int argc, char **argv, char **envp, t_fd_cont *fdc)
{
	fdc->infile = open_infile(argv[1], envp);
	if (fdc->infile == -1)
		return (-1);
	fdc->outfile = open_outfile(argv[argc - 1], envp);
	if (fdc->outfile == -1)
		return (-1);
	return (0);
}

static int	open_infile(char *infile, char **envp)
{
	int		fd;
	char 	*path;

	path = get_full_filepath(infile, envp);
	if (!path)
		return (-1);
	if (access(path, W_OK) == -1)
	{
		free(path);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

static int	open_outfile(char *outfile, char **envp)
{
	int		fd;
	char 	*path;

	path = get_full_filepath(outfile, envp);
	if (!path)
		return (-1);
	if (access(path, F_OK | W_OK) == 0)
		unlink(path);
	fd = open(path, O_WRONLY | O_CREAT, 00755);
	free(path);
	return (fd);
}
