/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/24 11:29:29 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 0
# define WRITE 1
# include <stdlib.h>

typedef struct s_pipex
{
	char	**envp;
	char	**env_path;
	char	*pwd;
	int		fd;
	int		p_fd[2];
}	t_pipex;

//////////////////////////////////////////////////////////////////// pipex.c //
int		init_pipex(t_pipex *px, char **envp);
void	fd_bzero(t_pipex *px);
int		close_all_fds(t_pipex *px);
int		close_pipex(t_pipex *px);
void	roll_pipe(t_pipex *px, int last);
///////////////////////////////////////////////////////////// get_env_path.c //
char	**get_env_path(char **envp);
char	*get_pwd(char **envp);
//////////////////////////////////////////////////////////////// arg_split.c //
char	**arg_split(char *arg);
void	free_av(char ***av);
/////////////////////////////////////////////////////////////////// get_av.c //
char	**get_av(char *arg, t_pipex *t);
/////////////////////////////////////////////////////////////////// error.c //
void	err_cmd_not_found(char *cmd);
void	err_with_filename(char *filename);
void	error_exit(t_pipex *px);
//////////////////////////////////////////////////////////// exec_commands.c //
void	exec_commands(int argc, char **argv, t_pipex *px);
/////////////////////////////////////////////////////////////// open_files.c //
void	open_infile(char *infile, t_pipex *px);
void	open_outfile(char *outfile, t_pipex *px);

#endif
