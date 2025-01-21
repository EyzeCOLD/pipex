/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/20 15:16:43 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 0
# define WRITE 1
# include <stdlib.h>

typedef struct s_pipex
{
	char	**env_path;
	char	*pwd;
	int		p_fd[2];
}	t_pipex;

//							pipex.c
int	init_pipex(t_pipex *px, char **envp);
int	close_pipex(t_pipex *px);

//							get_env_path.c
char	**get_env_path(char **envp);
char	*get_pwd(char **envp);

//							pipe_array.c
int	**init_pipearr(size_t pipes);
int	destroy_pipearr(int ***pipearr);

//							arg_split.c
char	**arg_split(char *arg);
void	free_av(char ***av);

//							get_av.c
void	free_av_arr(char ****av_array);

//							error.c
void	err_comm_not_found(char *cmd);
void	err_with_filename(char *filename);

//							exec_commands.c
int	exec_commands(size_t cmds, t_pipex *px, char **envp);

#endif
