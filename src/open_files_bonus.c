/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:18:15 by juaho             #+#    #+#             */
/*   Updated: 2025/01/24 11:14:42 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../inc/pipex_bonus.h"
#include "../libft/libft.h"

void	open_infile(char *infile, t_pipex *px)
{
	char	*infile_path;

	infile_path = ft_strjoinm(3, px->pwd, "/", infile);
	if (!infile_path)
		error_exit(px);
	px->fd = open(infile_path, O_RDONLY);
	if (px->fd < 0)
	{
		err_with_filename(infile);
		free(infile_path);
		close_pipex(px);
	}
	free(infile_path);
}

void	open_outfile(char *outfile, t_pipex *px)
{
	char	*outfile_path;

	outfile_path = ft_strjoinm(3, px->pwd, "/", outfile);
	if (!outfile_path)
		error_exit(px);
	px->fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (px->fd < 0)
	{
		err_with_filename(outfile);
		free(outfile_path);
		close_pipex(px);
	}
	free(outfile_path);
}
