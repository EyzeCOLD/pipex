/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:17:30 by juaho             #+#    #+#             */
/*   Updated: 2025/01/29 12:19:32 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "pipex.h"

//////////////////////////////////////////////////////////// heredoc_bonus.c //
void	heredoc_first_cmd(char *lim, char *arg, t_pipex *px);
void	heredoc_last_cmd(char *outfile, char *arg, t_pipex *px);

#endif
