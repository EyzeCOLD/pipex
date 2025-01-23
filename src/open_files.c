/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:18:15 by juaho             #+#    #+#             */
/*   Updated: 2025/01/22 09:42:00 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

int	open_infile(char *infile, t_pipex *px)
{
	char	*infile_path;
	int		infile_fd;

	infile_path = ft_strjoinm(3, px->pwd, "/", infile);
	if (!infile_path)
		error_exit(px);
	infile_fd = open(infile_path, O_RDONLY);
	if (infile < 0)
	{
		err_with_filename(infile);
		free(infile_path);
		close_pipex(px);
	}
	free(infile_path);
	return (infile_fd);
}

int	open_outfile(char *outfile, t_pipex *px)
{
	char	*outfile_path;
	int		outfile_fd;

	outfile_path = ft_strjoinm(3, px->pwd, "/", outfile);
	if (!outfile_path)
		error_exit(px);
	if (access(outfile_path, W_OK) == 0)
	{
		if (unlink(outfile_path) < 0)
		{
			perror("pipex");
			free(outfile_path);
			close_pipex(px);
		}
	}
	outfile_fd = open(outfile_path, O_WRONLY | O_CREAT, 00755);
	if (outfile_fd  < 0)
	{
		err_with_filename(outfile);
		free(outfile_path);
		close_pipex(px);
	}
	free(outfile_path);
	return (outfile_fd);
}
