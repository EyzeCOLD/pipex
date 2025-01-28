/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/27 16:50:58 by juaho            ###   ########.fr       */
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
	int		pipe_fd[2];
	int		prev_pipe_fd;
}	t_pipex;

////////////////////////////////////////////////////////////// pipex_bonus.c //
int		init_pipex(t_pipex *px, char **envp);
void	fd_bzero(t_pipex *px);
int		close_all_fds(t_pipex *px);
int		close_pipex(t_pipex *px);
void	roll_pipe(t_pipex *px, int last);
///////////////////////////////////////////////////////////// get_env_path.c //
char	**get_env_path(char **envp);
char	*get_pwd(char **envp);
char	*get_env_line(char *line, char **envp);
//////////////////////////////////////////////////////////////// arg_split.c //
char	**arg_split(char *arg);
void	free_av(char ***av);
///////////////////////////////////////////////////////////// get_av_bonus.c //
char	**get_av(char *arg, t_pipex *t);
////////////////////////////////////////////////////////////// error_bonus.c //
void	err_cmd_not_found(char *cmd);
void	err_perm_denied(char *cmd);
void	err_with_filename(char *filename);
void	error_exit(t_pipex *px, char *filename);
////////////////////////////////////////////////////// exec_commands_bonus.c //
void	first_cmd(char *infile, char *arg, t_pipex *px);
void	heredoc_first_cmd(char *arg, char *lim, t_pipex *px);
void	cmd(char *arg, t_pipex *px);
void	last_cmd(char *outfile, char *arg, t_pipex *px);
///////////////////////////////////////////////////////// open_files_bonus.c //
void	open_infile(char *infile, t_pipex *px);
void	open_outfile(char *outfile, t_pipex *px);
//////////////////////////////////////////////////////////// heredoc_bonus.c //
int		heredoc(char *limiter, t_pipex *px);

#endif
