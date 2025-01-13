/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/11 17:06:06 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

char	*get_cmd_path_for_execve(char **cmd, char **env_path);
char	**get_env_path(char	**envp);
char	**cmd_split(char *cmd);
void	free_arr(char ***arr);
int		fork_exec(char **av, char **envp);

#endif
