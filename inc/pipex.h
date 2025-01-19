/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/14 10:56:26 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>

typedef struct	s_fd_cont
{
	int		infile;
	int		outfile;
	int		**pipearr;
	size_t	pipes;
}	t_fd_cont;

// 		pipex.c
void	close_and_free_fd_cont(t_fd_cont *fdc);
//		open_files
int		open_files(int argc, char **argv, char **envp, t_fd_cont *fdc);
//		get_env.c
char	**env_path_split(char **envp);
char	*get_pwd(char **envp);
//		expand_cmd_path.c
char	**arg_to_av_for_execve(char *arg, char **envp);
char	*get_full_filepath(char *file, char **envp);

char	**cmd_split(char *cmd);
void	free_arr(char ***arr);
int		fork_exec(char **av, int in_fd, int out_fd, t_fd_cont *fdc);
int		**pipe_array(size_t n);
void	close_and_free_pipe_arr(int ***arr, size_t size);

#endif
