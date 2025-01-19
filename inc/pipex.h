/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:32:05 by juaho             #+#    #+#             */
/*   Updated: 2025/01/19 16:10:53 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>

typedef struct s_pipex
{
	char	**env_path;
	char	*pwd;
	char	*infile_path;
	int		infile_fd;
	char	*outfile_path;
	int		outfile_fd;
	int		**pipe_arr;
	int		***av_arr;
}	t_pipex;

//	pipex.c
int	destroy_pipex(t_pipex *px);
//	get_env_path.c
char	**get_env_path(char **envp);
char	*get_pwd(char **envp);
//	pipe_array.c
int	**init_pipearr(size_t pipes);
int	destroy_pipearr(int ***pipearr);

#endif
