/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:11:51 by juaho             #+#    #+#             */
/*   Updated: 2025/01/19 20:40:51 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../inc/pipex.h"
#include "../libft/libft.h"

static int	init_pipex(t_pipex *px, int argc, char **argv, char **envp);

int main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (0);

}

static void	pipex_bzero(t_pipex *px)
{
	px->env_path = NULL;
	px->pwd = NULL;
	px->infile_path = NULL;
	px->infile_fd = -1;
	px->outfile_path = NULL;
	px->outfile_fd = -1;
	px->pipe_arr = NULL;
	px->av_arr = NULL;
}

static int	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
{
	pipex_bzero(px);
	px->env_path = get_env_path(envp);
	px->pwd = get_pwd(envp);
	px->infile_path = ft_strjoinm(3, px->pwd, "/", argv[1]);
	px->infile_fd = open(px->infile_path, O_RDONLY);
	px->outfile_path = ft_strjoinm(3, px->pwd, "/", argv[argc - 1]);
	px->outfile_fd = open(px->outfile_path, O_CREAT | O_WRONLY, 00755);
	px->pipe_arr = init_pipearr((size_t) argc - 4);
	px->av_arr = get_av_arr(argc, argv, px->env_path, px->pwd);
	return (0);
}

int	destroy_pipex(t_pipex *px)
{
	int	error;

	error = 0;
	if (px->env_path)
		free_av(&(px->env_path));
	free(px->pwd);
	free(px->infile_path);
	if (close(px->infile_fd) < 0)
		error = -1;
	free(px->outfile_path);
	if (close(px->outfile_fd) < 0)
		error = -1;
	if (destroy_pipearr(&(px->pipe_arr)) < 0)
		error = -1;
	free_av_arr(&(px->av_arr));
	return (error);
}
