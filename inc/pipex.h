/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/30 12:07:49 by juaho            ###   ########.fr       */
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
	int		fd;
	int		pipe_fd[2];
	int		prev_pipe_fd;
}	t_pipex;

//////////////////////////////////////////////////////////////////// pipex.c //
void	init_pipex(t_pipex *px, char **envp);
void	fd_bzero(t_pipex *px);
int		close_all_fds(t_pipex *px);
int		close_pipex(t_pipex *px, int exit_status);
void	roll_pipe(t_pipex *px, int last);
///////////////////////////////////////////////////////////// get_env_path.c //
char	**get_env_path(char **envp);
char	*get_env_line(char *line, char **envp);
//////////////////////////////////////////////////////////////// arg_split.c //
char	**arg_split(char *arg);
////////////////////////////////////////////////////////////////// free_av.c // 
void	free_av(char ***av);
/////////////////////////////////////////////////////////////////// get_av.c //
char	**get_av(char *arg, t_pipex *t);
//////////////////////////////////////////////////////////////////// error.c //
int		err_cmd_not_found(char *cmd);
int		err_perm_denied(char *cmd);
int		err_with_filename(char *filename);
void	error_exit(t_pipex *px, char *filename);
//////////////////////////////////////////////////////////// exec_commands.c //
void	first_cmd(char *infile, char *arg, t_pipex *px);
pid_t	last_cmd(char *outfile, char *arg, t_pipex *px);
void	cmd_exec(char **av, t_pipex *px);
//////////////////////////////////////////////////////////////// open_file.c //
void	open_file(char *infile, t_pipex *px, int flags);

#endif
