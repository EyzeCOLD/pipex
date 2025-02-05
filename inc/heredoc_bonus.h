/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:17:30 by juaho             #+#    #+#             */
/*   Updated: 2025/02/04 14:46:42 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "pipex.h"

//////////////////////////////////////////////////////////// heredoc_bonus.c //
void	get_heredoc_input(char *lim, t_pipex *px);
pid_t	heredoc_last_cmd(char *outfile, char *arg, t_pipex *px);

#endif
