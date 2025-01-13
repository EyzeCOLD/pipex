/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/13 20:04:49 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>

//		get_env.c
char	**get_path_arr(char **envp);
char	*get_pwd(char **envp);
//		expand_cmd_path.c
int		expand_cmd_path(char **cmd, char **env_path);

char	**cmd_split(char *cmd);
void	free_arr(char ***arr);
int		fork_exec(char **av, char **envp);
int		**pipe_array(size_t n);
void	close_and_free_pipe_arr(int ***arr, size_t size);

#endif
